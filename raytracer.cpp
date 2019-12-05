/***************************************************************************
 *
 * ohe21 - Oliver's Raytracer
 *
 */

/*
 * g++ -o finalexecutable raytracer.cpp framebuffer.cpp linedrawer.cpp camera.cpp sphere.cpp scene.cpp plane.cpp triangle.cpp polymesh.cpp material.cpp spotlight.cpp pointlight.cpp alglibmisc.cpp alglibinternal.cpp ap.cpp -lm -O3
 *
 * Execute the code using ./finalexecutable
 *
 * pnmtopng test.ppm > test.png
 */


#include <limits>
#include <stdlib.h>
#include <time.h>

#include "framebuffer.h"
#include "camera.h"
#include "vector.h"
#include "vertex.h"
#include "scene.h"
#include "ray.h"
#include "hit.h"
#include "object.h"
#include "colour.h"
#include "photon.h"
#include "photonmap.h"


Hit checkForIntersection(Ray ray, float t, Hit closest, std::vector<Object*> objs){
  Hit new_t = Hit();
  for (int i = 0; i < objs.size(); i++) {
    objs[i]->intersection(ray, new_t);
    if (new_t.flag)
    {
      if (new_t.t < t)
      {
        t = new_t.t;
        closest = new_t;
      }
    }
  }
  return closest;
}

Vector getLightDir(std::vector<Light*> lights, int iLight, Hit hitObj){
  Vector lightDir;
  try{
    lightDir = lights[iLight]->getDirection();
  } catch(const std::exception e){
    lightDir = lights[iLight]->getDirection(hitObj.position);
  }
  return lightDir;
}

bool checkForShadow(Hit closest, std::vector<Object*> objs, Ray ray, Light* light){
    Hit new_t = Hit();
    float light_distance = light->getDistance(closest.position);
    for (int i = 0; i < objs.size(); i++) {
      objs[i]->intersection(ray, new_t);

      if (new_t.flag && ((light_distance-new_t.t) >= 0)) return true;
    }
    return false;
  };


float fresnel(Vector lRayDir, Vector N, float ior){
    float cosi = N.dot(lRayDir);
    cosi = std::min(1.0f, std::max(cosi, -1.0f));
    float etai = 1, etat = ior;
    if (cosi > 0) { std::swap(etai, etat); }
    // Compute sini using Snell's law
    float sint = etai / etat * sqrtf(std::max(0.f, 1 - cosi * cosi));
    // Total internal reflection
    if (sint >= 1) {
        float kr = 1;
        return kr;
    } else {
        float cost = sqrtf(std::max(0.f, 1 - sint * sint));
        cosi = fabsf(cosi);
        float Rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost));
        float Rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost));
        float kr = (Rs * Rs + Rp * Rp) / 2;
        return kr;
    }
    // As a consequence of the conservation of energy, transmittance is given by:
    // kt = 1 - kr;

}

Colour raytrace(Scene *sc, Camera *camera, Ray lRay, int depth){
  Colour colour = Colour();

  Hit closest = Hit();
  closest.t = std::numeric_limits<int>::max();
  closest = checkForIntersection(lRay, closest.t, closest, sc->objects);

  if (closest.t != std::numeric_limits<int>::max()){

    colour = closest.what->objMaterial->computeBaseColour();

    if (depth == 0) return colour;

    Vector SurfaceNormal = closest.normal;
    for (float iLight = 0; iLight < sc->lights.size(); iLight++){
      Vector lightDir = getLightDir(sc->lights, iLight, closest);
      lightDir.negate();
      float diff = SurfaceNormal.dot(lightDir);
      if (diff > 0.0f){
        Ray shadowRay = Ray(closest.position + lightDir.multiply(0.0001f), lightDir);
        if(!checkForShadow(closest, sc->objects, shadowRay, sc->lights[iLight])){
          Colour scale = sc->lights[iLight]->getIntensity();
          Colour intensity = closest.what->objMaterial->compute_light_colour(SurfaceNormal, camera->e - closest.position, lightDir, diff);
          colour += intensity * scale;
        }
      }
    }

    if(closest.what->objMaterial->isReflective && closest.what->objMaterial->isTransparent){

        Colour refractionColour = Colour();
        float kr = fresnel(lRay.direction, SurfaceNormal, closest.what->objMaterial->ior);

        if (kr < 1) {
          Vector refraction;
          lRay.direction.normalise();
          Vector bias = closest.normal.multiply(0.001f);
          bool outside = lRay.direction.dot(SurfaceNormal) < 0;
          SurfaceNormal.refraction(lRay.direction, closest.what->objMaterial->ior, refraction);
          refraction.normalise();
          Vertex origin = outside ? closest.position - bias  : closest.position + bias;
          Ray transparentRay = Ray(origin, refraction);
          refractionColour += raytrace(sc, camera, transparentRay, depth-1) * closest.what->objMaterial->transparentDegree;
        }

        Vector r;
        SurfaceNormal.reflection(lRay.direction, r);
        r.normalise();
        Ray reflectionRay = Ray(closest.position + r.multiply(0.001f), r);
        Colour reflectionColour = raytrace(sc, camera, reflectionRay, depth-1) * closest.what->objMaterial->reflectionDegree;

        colour += reflectionColour * kr + refractionColour * (1 - kr);
    } else {
      if(closest.what->objMaterial->isReflective){
        Vector r;
        SurfaceNormal.reflection(lRay.direction, r);
        r.normalise();
        Ray reflectionRay = Ray(closest.position + r.multiply(0.001f), r);

        colour += raytrace(sc, camera, reflectionRay, depth-1) * closest.what->objMaterial->reflectionDegree;
      }
    }

  }
  return colour;
}

Colour photontrace(Scene *sc, Camera *camera, Ray pRay, std::vector<Photon> &photonHitsMap){
  Colour colour = Colour();

  Hit closest = Hit();
  closest.t = std::numeric_limits<int>::max();
  closest = checkForIntersection(pRay, closest.t, closest, sc->objects);

  if (closest.t != std::numeric_limits<int>::max()){
    colour = closest.what->objMaterial->computeBaseColour();

    float probDiffuse = (pRay.photon.power * closest.what->objMaterial->diffuse).getStrength() / pRay.photon.power.getStrength();
    float probSpecular = (pRay.photon.power * closest.what->objMaterial->specular).getStrength() / pRay.photon.power.getStrength();
    float probAbsorbtion = 1 - (probDiffuse + probSpecular);

    float r = (float) ((rand() % 100) + 1) / 100; // 0.00 to 1.00

    // switch to determine type of ray
    if (0 <= r && r < probDiffuse){
      // diffuse reflection : calc power of new photon and trace it recursively until absorbtion
      Vector r;
      closest.normal.reflection(pRay.direction, r);
      r.normalise();
      pRay.photon.addColour(closest.what->objMaterial->computeBaseColour());
      pRay.photon.calcReflectionPower(probDiffuse, closest.what->objMaterial->diffuse);
      Ray photonRay = Ray(closest.position, r.multiply(0.001f), pRay.photon);
      colour += photontrace(sc, camera, photonRay, photonHitsMap);
      // store photon-surface interaction
      pRay.photon.storePosition(closest);
      photonHitsMap.push_back(pRay.photon);
    } else if (probDiffuse <= r && r < probDiffuse+probSpecular){
      // specular reflection : calc power of new photon and trace it recursively until absorbtion
      Vector r;
      closest.normal.reflection(pRay.direction, r);
      r.normalise();
      pRay.photon.addColour(closest.what->objMaterial->computeBaseColour());
      pRay.photon.calcReflectionPower(probSpecular, closest.what->objMaterial->specular);
      Ray photonRay = Ray(closest.position, r.multiply(0.001f), pRay.photon);
      colour += photontrace(sc, camera, photonRay, photonHitsMap);
    } else if (probDiffuse+probSpecular <= r && r <= 1) {
      // absorbed
      // store photon-surface interaction
      // pRay.photon.addColour(closest.what->objMaterial->computeBaseColour());
      pRay.photon.storePosition(closest);
      photonHitsMap.push_back(pRay.photon);
    }
  }

  return colour;
}

PhotonMap createPhotonMap(Scene *sc, Camera *camera){
  int scale = 100000;
  std::vector<Photon> photonHitsMap;
  PhotonMap pm;
  for (float iLight = 0; iLight < sc->lights.size(); iLight++){
    int n_emittedPhotons = 0;
    Vector pDir; Vertex pPos;
    while (n_emittedPhotons < scale * sc->lights[iLight]->getStrength()){
      pDir = sc->lights[iLight]->getRandEmittionDirection();
      pPos = sc->lights[iLight]->getRandEmittionPosition();

      Photon ph = Photon(sc->lights[iLight]->getIntensity());

      // trace from pPos to pDir
      Ray photonRay = Ray(pPos, pDir, ph);
      photontrace(sc, camera, photonRay, photonHitsMap);

      n_emittedPhotons ++;
    }
  }

  // Add to KD Tree
  // TODO: Scale tree? - take account of min max ?
  pm.populateMap(photonHitsMap);
  return pm;  
}

int main(int argc, char *argv[]){
    using namespace alglib_impl;

  // https://stackoverflow.com/questions/686353/random-float-number-generation
  srand (static_cast <unsigned> (time(0)));

  // Create Camera
  Vertex eye = Vertex(0, 0, 0);
  Vertex look = Vertex(0, 0, 7);
  Vector up = Vector(0, 1, 0);
  float dist = 700;
  float FOV = 0.9; // RAD
  Camera *camera = new Camera(eye, look, up, dist, FOV);

  // Create a framebuffer
  Scene *sc = new Scene(1024, 1024); // 2048
  FrameBuffer *fb = new FrameBuffer(sc->width, sc->height);

  // Create PhotonMap
  PhotonMap pm = createPhotonMap(sc, camera);

   for (int x = 0; x <= sc->width - 1; x++)
   {
     for (int y = 0; y <= sc->height - 1; y++)
     {
       Ray ray = camera->getRay(sc, x, y);
       int depth = 4;
       Colour baseColour = raytrace(sc, camera, ray, depth);
       fb->plotPixel(x, y, baseColour.R, baseColour.G, baseColour.B);
     }
   }

  // Output the framebuffer.
  fb->writeRGBFile((char *)"test.ppm");

  return 0;

}

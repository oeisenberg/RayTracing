/***************************************************************************
 *
 * ohe21 - Oliver's Raytracer
 *
 */

/*
 * g++ -o finalexecutable raytracer.cpp framebuffer.cpp linedrawer.cpp camera.cpp sphere.cpp scene.cpp plane.cpp triangle.cpp polymesh.cpp material.cpp diffuse.cpp ambient.cpp specular.cpp spotlight.cpp pointlight.cpp -lm -O3
 *
 * Execute the code using ./finalexecutable
 *
 * pnmtopng test.ppm > test.png
 */

#include <iostream>
#include <limits>
#include "framebuffer.h"
#include "linedrawer.h"
#include "camera.h"
#include "vector.h"
#include "vertex.h"
#include "sphere.h"
#include "scene.h"
#include "ray.h"
#include "hit.h"
#include "object.h"
#include "colour.h"

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

Colour getLightCoefficients(Scene *sc, Camera *camera, Hit closest, Object *obj){
  Colour dCoeff = sc->DiffuseLightModel->getCoeff(sc->lights, sc->objects, closest, obj->dCoeff);
  Colour sCoeff = sc->SpecularLightModel->getCoeff(sc->lights, sc->objects, closest, camera->e, obj->sCoeff);
  Colour coeff = dCoeff + sCoeff;
  coeff += sc->AmbientLightModel->getCoeff(obj->aCoeff);
  // coeff += reflectionRayTrace(sc, camera, obj);
  return coeff;
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

Colour raytrace(Scene *sc, Camera *camera, Ray lRay, int depth){
  Colour colour;

  Hit closest = Hit();
  closest.t = std::numeric_limits<int>::max();
  closest = checkForIntersection(lRay, closest.t, closest, sc->objects);

<<<<<<< HEAD
  hit.t = std::numeric_limits<int>::max();
  hit = checkForIntersection(ray, hit.t, hit, objs);
  if(hit.flag){
    colour = hit.what.reflectiveValue *
      for (float iLight = 0; iLight < sc->lights.size(); iLight++){
        float coeff = getLightCoefficients(sc, camera, hit, hit.what);
        Vector reflection;
        SurfaceNormal.reflection(lightDir, reflection);
        colour += hit.what.reflectiveValue * reflectionRayTrace(sc, camera, rray, depth-1, objs);
      }
  }
=======
  if (closest.t != std::numeric_limits<int>::max()){

    colour = closest.what->objMaterial->computeBaseColour();

    if (depth == 0) return colour;

    Vector SurfaceNormal = closest.normal;
    for (float iLight = 0; iLight < sc->lights.size(); iLight++){
      Vector lightDir = getLightDir(sc->lights, iLight, closest);
      lightDir.negate();
      float diff = SurfaceNormal.dot(lightDir);
      if (diff > 0.0f){
        Ray shadowRay = Ray(closest.position + lightDir.multiply(1), lightDir);
        if(!checkForShadow(closest, sc->objects, shadowRay, sc->lights[iLight])){
          Colour scale = sc->lights[iLight]->getIntensity();
          Colour intensity = closest.what->objMaterial->compute_light_colour(SurfaceNormal, camera->e - closest.position, lightDir, diff);
          colour += intensity * scale;
        }
      }
    }

    // TODO: compute reflection ray if material supports it.
    if(closest.what->objMaterial->isReflective){
      Vector r;
      SurfaceNormal.reflection(lRay.direction, r);
      Ray reflectionRay = Ray(closest.position + r.multiply(1), r);
>>>>>>> ce94bd8b6ba00acc78be880af9220c6dcd311f47

      colour += raytrace(sc, camera, reflectionRay, depth-1) * 0.5;
    }

    // TODO: compute refraction ray if material supports it.
    if(closest.what->objMaterial->isTransparent){
      
    }
  }
  return colour;
}

int main(int argc, char *argv[])
{
  // Create Camera
  Vertex eye = Vertex(0, 0, 0);
  Vertex look = Vertex(0, 0, 7);
  Vector up = Vector(0, 1, 0);
  float dist = 350;
  float FOV = 1; // RAD
  Camera *camera = new Camera(eye, look, up, dist, FOV);

  // Create a framebuffer
  Scene *sc = new Scene(600, 600); // 2048
  FrameBuffer *fb = new FrameBuffer(sc->width, sc->height);

  for (int x = 0; x <= sc->width - 1; x++)
  {
    for (int y = 0; y <= sc->height - 1; y++)
    {
      Ray ray = camera->getRay(sc, x, y);
      int depth = 2;
      Colour baseColour = raytrace(sc, camera, ray, depth);
      fb->plotPixel(x, y, baseColour.R, baseColour.G, baseColour.B);
    }
  }

  // Output the framebuffer.
  fb->writeRGBFile((char *)"test.ppm");

  return 0;

}

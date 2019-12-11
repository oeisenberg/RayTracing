/***************************************************************************
 *
 * ohe21 - Oliver's Raytracer
 *
 */

/*
 * g++ -o finalexecutable tracing.cpp framebuffer.cpp linedrawer.cpp camera.cpp sphere.cpp scene.cpp plane.cpp triangle.cpp polymesh.cpp material.cpp spotlight.cpp pointlight.cpp alglibmisc.cpp alglibinternal.cpp ap.cpp -lm -O3
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
#include "rayTracer.h"
#include "photonTracer.h"

PhotonMap createGlobalPhotonMap(Scene scene, Camera camera, PhotonTracer pt, int scale, int nSamples){
  std::vector<Photon> photonHitsMap;
  PhotonMap pm(nSamples);
  for (float iLight = 0; iLight < scene.lights.size(); iLight++){
    int n_emittedPhotons = 0;
    Vector pDir; Vertex pPos;
    while (n_emittedPhotons < scale *  scene.lights[iLight]->getStrength()){
      pDir = scene.lights[iLight]->getRandEmittionDirection();
      pPos = scene.lights[iLight]->getRandEmittionPosition();

      Photon photonRay = Photon("direct", pPos, pDir,  scene.lights[iLight]->getIntensity() / scale);
      pt.photontrace(scene, camera, photonRay, photonHitsMap);

      n_emittedPhotons ++;
    } 
  }

  pm.populateMap(photonHitsMap);             
  return pm;  
}

PhotonMap createCausticPhotonMap(Scene scene, Camera camera, PhotonTracer pt, int scale, int nSamples){
  std::vector<Photon> photonHitsMap;
  PhotonMap pm(nSamples);
  for (float iLight = 0; iLight < scene.lights.size(); iLight++){
    for (float iObj = 0; iObj < scene.objects.size(); iObj++){
      if (scene.objects[iObj]->objMaterial->isTransparent || scene.objects[iObj]->objMaterial->isReflective){
        int n_emittedPhotons = 0;
        Vector pDir; Vertex pPos;
        while (n_emittedPhotons < scale * scene.lights[iLight]->getStrength()){
          pPos = scene.lights[iLight]->getRandEmittionPosition();
          pDir = scene.objects[iObj]->calcSurfacePoint() - pPos;
          pDir.normalise();

          Photon photonRay = Photon("caustic", pPos, pDir, scene.lights[iLight]->getIntensity() / scale);
          pt.photontrace(scene, camera, photonRay, photonHitsMap);

          n_emittedPhotons ++; 
        }
      }
    }
  }

  pm.populateMap(photonHitsMap);             
  return pm;  
}

int main(int argc, char *argv[]){
    using namespace alglib_impl; // https://www.alglib.net/translator/man/manual.cpp.html

  // https://stackoverflow.com/questions/686353/random-float-number-generation
  srand (static_cast <unsigned> (time(0)));

  // Create Camera
  Vertex eye = Vertex(0, 0, 0);
  Vertex look = Vertex(0, 0, 7);
  Vector up = Vector(0, 1, 0);
  float dist = 150;
  float FOV = 0.9; // RAD
  Camera *camera = new Camera(eye, look, up, dist, FOV);

  // Create a framebuffer
  Scene *sc = new Scene(256, 256);
  FrameBuffer *fb = new FrameBuffer(sc->width, sc->height);

  // // Create gloabl photon map
  PhotonTracer *pta = new PhotonTracer();
  PhotonMap gloabalPm = createGlobalPhotonMap(*sc, *camera, *pta, 1000000, 200);
  // Create caustic photon map
  PhotonTracer *ptb = new PhotonTracer();
  PhotonMap causticPm = createCausticPhotonMap(*sc, *camera, *ptb, 10000, 200);

  std::cout << "Finished building the KD Tree" << std::endl;

  for (int x = 0; x <= sc->width - 1; x++)
  {
    for (int y = 0; y <= sc->height - 1; y++)
    { 
      Ray ray = camera->getRay(sc, x, y);
      int depth = 4;
      RayTracer rt = RayTracer();
      Colour baseColour = rt.raytrace(*sc, *camera, ray, depth, gloabalPm, causticPm);
      // std::cout << baseColour.R << ", " << baseColour.G << ", " << baseColour.B << std::endl;
      fb->plotPixel(x, y, baseColour.R, baseColour.G, baseColour.B);
    }
    std::cout << "Col " << x << std::endl;
  }

  fb->writeRGBFile((char *)"test.ppm");

  // Output the framebuffer.
  std::cout << "Applying blur" << std::endl;
  fb->gaussianBlur();
  fb->writeRGBFile((char *)"test-blur.ppm");


  return 0;

}

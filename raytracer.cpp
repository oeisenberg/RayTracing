/***************************************************************************
 *
 * ohe21 - Oliver's Raytracer
 *
 */

/*
 * g++ -o finalexecutable raytracer.cpp framebuffer.cpp linedrawer.cpp camera.cpp sphere.cpp scene.cpp triangle.cpp polymesh.cpp material.cpp diffuse.cpp ambient.cpp specular.cpp spotlight.cpp pointlight.h material.cpp -lm -O3
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

float checkForShadowIntersection(Hit closest, std::vector<Object*> objs, std::vector<Light*> lights){
  int numbOfLights = lights.size();
  float steps = 1.0/numbOfLights;
  float shadowCoeff = 1;

  for (int iLight = 0; iLight < numbOfLights; iLight++){
    Vector lightDir; // = lights[iLight]->getDirection();
    try{
      lightDir = lights[iLight]->getDirection();
    } catch(const std::exception e){
      lightDir = lights[iLight]->getDirection(closest.position);
    }
    Ray ray = Ray(closest.position + lightDir.multiply(1), lightDir);
    Hit new_t = Hit();
    for (int i = 0; i < objs.size(); i++) {
      objs[i]->intersection(ray, new_t);

      if (new_t.flag)
      {
        // Reduce by step count
        shadowCoeff -= steps;
        // No need to test for all other objects once a shadow is confirmed
        break;
      }
    }
  }

  return shadowCoeff;
}

int main(int argc, char *argv[])
{
  // Create Camera
  Vertex eye = Vertex(0, 0, 0);
  Vertex look = Vertex(0, 0, 7);
  Vector up = Vector(0, 1, 0);
  float dist = 200;
  float FOV = 1; // RAD
  Camera *camera = new Camera(eye, look, up, dist, FOV);

  // Create a framebuffer
  Scene *sc = new Scene(400, 400); // 2048
  FrameBuffer *fb = new FrameBuffer(sc->width, sc->height);

  for (int x = 0; x <= sc->width - 1; x++)
  {
    for (int y = 0; y <= sc->height - 1; y++)
    {
      Ray ray = camera->getRay(sc, x, y);
      Hit closest = Hit();
      closest.t = std::numeric_limits<int>::max();
      closest = checkForIntersection(ray, closest.t, closest, sc->objects);
      float shadowCoeff = checkForShadowIntersection(closest, sc->objects, sc->lights);

      if (closest.t != std::numeric_limits<int>::max())
      {
        Object *obj = closest.what;
        float dCoeff = sc->DiffuseLightModel->getCoeff(sc->lights, closest, obj->dCoeff);
        float sCoeff = sc->SpecularLightModel->getCoeff(sc->lights, closest, camera->e, obj->sCoeff);
        float coeff = dCoeff + sCoeff;

        coeff *= shadowCoeff;
        coeff += sc->AmbientLightModel->getCoeff(obj->aCoeff);
        fb->plotPixel(x, y, obj->R*coeff, obj->G*coeff, obj->B*coeff);
      }

    }
  }

  // Output the framebuffer.
  fb->writeRGBFile((char *)"test.ppm");

  return 0;

}

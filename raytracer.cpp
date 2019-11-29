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

Colour reflectionRayTrace(Scene *sc, Camera *camera, Ray &ray, int depth, std::vector<Object*> objs){
  Colour colour;
  Hit hit;
  colour.clear();

  if (depth == 0) return colour;

  hit.t = std::numeric_limits<int>::max();
  hit = checkForIntersection(ray, hit.t, hit, objs);
  if(hit.flag){
    // colour = hit.what.reflectiveValue *
      // for (float iLight = 0; iLight < sc->lights.size(); iLight++){
      //   float coeff = getLightCoefficients(sc, camera, hit, hit.what);
      //   Vector reflection;
      //   SurfaceNormal.reflection(lightDir, reflection);
      //   colour += hit.what.reflectiveValue * reflectionRayTrace(sc, camera, rray, depth-1, objs);
      // }
  }

}

int main(int argc, char *argv[])
{
  // Create Camera
  Vertex eye = Vertex(0, 0, 0);
  Vertex look = Vertex(0, 0, 7);
  Vector up = Vector(0, 1, 0);
  float dist = 250;
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

      if (closest.t != std::numeric_limits<int>::max())
      {
        Object *obj = closest.what;
        Colour coeff = getLightCoefficients(sc, camera, closest, closest.what);
        fb->plotPixel(x, y, coeff.R, coeff.G, coeff.B);
      }

    }
  }

  // Output the framebuffer.
  fb->writeRGBFile((char *)"test.ppm");

  return 0;

}

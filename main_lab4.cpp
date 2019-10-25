/***************************************************************************
 *
 * krt - Kens Raytracer - Coursework Edition. (C) Copyright 1997-2019.
 *
 * Do what you like with this code as long as you retain this comment.
 */

/*
 * g++ -o lab4executable main_lab4.cpp framebuffer.cpp linedrawer.cpp camera.cpp sphere.cpp scene.cpp triangle.cpp polymesh.cpp diffuse.cpp ambient.cpp -lm -O3
 *
 * Execute the code using ./lab4executable
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

int main(int argc, char *argv[])
{
  // Create Camera
  Vertex eye = Vertex(0, 0, 0);
  Vertex look = Vertex(0, 0, 7);
  Vector up = Vector(0, 1, 0);
  float dist = 1200;
  float FOV = 1; // RAD
  Camera *camera = new Camera(eye, look, up, dist, FOV);

  // Create a framebuffer
  Scene *sc = new Scene(1500, 1500); // 2048
  FrameBuffer *fb = new FrameBuffer(sc->width, sc->height);

  std::vector<Object*> objs = sc->objects;

  for (int x = 0; x <= sc->width - 1; x++)
  {
    for (int y = 0; y <= sc->height - 1; y++)
    {
      Ray ray = camera->getRay(sc, x, y);
      float t = std::numeric_limits<int>::max();
      Hit closest = Hit();
      Hit new_t = Hit();
      for (int i = 0; i < sc->objects.size(); i++) {
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

      if (t != std::numeric_limits<int>::max())
      {
        // fb->plotDepth(x, y, closest.t);
        Object *obj = closest.what;
        float aCoeff = sc->AmbientLightModel->getCoeff();
        float dCoeff = sc->DiffuseLightModel->getCoeff(closest.normal, obj->dCoeff);
        float pCoeff = sc->PhongLightModel->getCoeff(closest.normal, camera->e, closest.position);
        float coeff = pCoeff;
        // float coeff = aCoeff + dCoeff;
        // float coeff = aCoeff + dCoeff + pCoeff;

        fb->plotPixel(x, y, obj->R*coeff, obj->G*coeff, obj->B*coeff);
      }

    }
  }

  // Output the framebuffer.
  // fb->writeDepthFile((char *)"test.ppm");
  fb->writeRGBFile((char *)"test.ppm");

  return 0;

}

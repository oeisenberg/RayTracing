/***************************************************************************
 *
 * krt - Kens Raytracer - Coursework Edition. (C) Copyright 1997-2019.
 *
 * Do what you like with this code as long as you retain this comment.
 */

/*
 * g++ -o lab3executable main_lab3.cpp framebuffer.cpp linedrawer.cpp camera.cpp sphere.cpp scene.cpp -lm
 * // polymesh.cpp  - error using stoi?
 *
 * Execute the code using ./lab3executable
 *
 * pnmtopng test.ppm > test.png
 */

#include <iostream>
#include <limits>
#include "framebuffer.h"
#include "linedrawer.h"
#include "polymesh.h"
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
  Vertex look = Vertex(5, 5, 5);
  Vector up = Vector(0, 1, 0);
  float dist = 40;
  float FOV = 0.628132; // RAD
  Camera *camera = new Camera(eye, look, up, dist, FOV);

  // Create obj (Sphere)
  int nObjs = 1;
  Sphere *sphereA = new Sphere(Vertex(7,7,7), 10);
  //Object *spheres = new Object[nObjs];
  //spheres[0] = *sphereA;

  // Create a framebuffer
  Scene *sc = new Scene(2048, 2048);
  FrameBuffer *fb = new FrameBuffer(sc->width, sc->height);

  for (int x = 0; x <= sc->width - 1; x++)
  {
    for (int y = 0; y <= sc->height - 1; y++)
    {
      Ray ray = camera->getRay(sc, x, y);
      float t = std::numeric_limits<int>::max();
      //Object *closest = NULL;
      for (int i = 0; i < nObjs; i++) {
        Hit new_t = Hit();
        //spheres[i].intersection(ray, new_t);
        sphereA->intersection(ray, new_t);
        if (new_t.flag == true)
        {
            if (new_t.t < t)
            {
              t = new_t.t;
              //closest = *spheres[i];
            }
            fb->plotDepth(x, y, new_t.t);
          }
      }
    }
  }

		/*
		*	calculate planes
		*	Store planes
		*
		*	get point P by checking intersection of the plane with a triangle
		*
		*	cal w1, w2.
		*	w1 = (Ax(Cy-Ay)+(Py-Ay)(Cx-Ax)-Px(Cy-Ay) / (By-Ay)(Cx-Ax) - (Bx - Ax)(Cy - Ay)
		*	w2 = Py - Ay - w1(By - Ay) / (Cy - Ay)
		*
		*	Point P is inside if w1 >= 0, w2 >= 0, (w1 + w2) <= 1
		*/


  // Output the framebuffer.
   fb->writeDepthFile((char *)"test.ppm");

  return 0;

}

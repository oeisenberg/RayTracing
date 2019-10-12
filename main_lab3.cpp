/***************************************************************************
 *
 * krt - Kens Raytracer - Coursework Edition. (C) Copyright 1997-2019.
 *
 * Do what you like with this code as long as you retain this comment.
 */

/*
 * g++ -o lab3executable main_lab3.cpp framebuffer.cpp linedrawer.cpp camera.cpp -lm
 * // polymesh.cpp  - error using stoi?
 *
 * Execute the code using ./lab3executable
 *
 * pnmtopng test.ppm > test.png
 */

#include <iostream>
#include "framebuffer.h"
#include "linedrawer.h"
#include "polymesh.h"
#include "camera.h"
#include "vector.h"
#include "vertex.h"

int main(int argc, char *argv[])
{
  // Create a framebuffer
  FrameBuffer *fb = new FrameBuffer(2048,2048);

  // create Camera
  Vertex eye = Vertex(0, 0, 0);
  Vertex look = Vertex(5, 5, 5);
  Vector up = Vector(1, 4, 9);
  float dist = 5.555;
  Camera *camera = new Camera(eye, look, up, dist);

  std::cout << "w: ("<< camera->w.x << ", " << camera->w.y << ", " << camera->w.z << ")" << std::endl;
  std::cout << "u: ("<< camera->u.x << ", " << camera->u.y << ", " << camera->u.z << ")" << std::endl;
  std::cout << "v: ("<< camera->v.x << ", " << camera->v.y << ", " << camera->v.z << ")" << std::endl;

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


	// Run Ray tracer ?


  // Output the framebuffer.
  //fb->writeRGBFile((char *)"test.ppm");

  return 0;

}

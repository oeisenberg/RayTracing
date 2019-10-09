/***************************************************************************
 *
 * krt - Kens Raytracer - Coursework Edition. (C) Copyright 1997-2019.
 *
 * Do what you like with this code as long as you retain this comment.
 */

/* This is the entry point function for the program you need to create for lab two.
 * You should not need to modify this code.
 * It creates a framebuffer, loads an triangle mesh object, calls the drawing function to render the object and then outputs the framebuffer as a ppm file.
 *
 * On linux.bath.ac.uk:
 *
 * Compile the code using g++ -o lab2executable main_lab2.cpp framebuffer.cpp linedrawer.cpp polymesh.cpp -lm
 *
 * Execute the code using ./lab2executable
 *
 * This will produce an image file called test.ppm. You can convert this a png file for viewing using
 *
 * pnmtopng test.ppm > test.png
 *
 * You are expected to fill in the missing code in polymesh.cpp.
 */

#include "framebuffer.h"
#include "linedrawer.h"
#include "polymesh.h"

using namespace std;

int main(int argc, char *argv[])
{
  // Create a framebuffer
  FrameBuffer *fb = new FrameBuffer(2048,2048);

  // The following transform allows 4D homogeneous coordinates to be transformed. It moves the supplied teapot model to somewhere visible.
  Transform *transform = new Transform(1.0f, 0.0f, 0.0f, 0.0f,0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 7.0f,0.0f,0.0f,0.0f,1.0f);

  // Read in the teapot model.
  PolyMesh *pm = new PolyMesh((char *)"teapot.ply", transform);

  // Create RayTracer


  // For each triangle in the model,
   for (int i = 0; i< pm->triangle_count; i += 1)
  {
   // The following lines project the point onto the 2D image from 3D space.
    float x0 = (pm->vertex[pm->triangle[i][0]].x/pm->vertex[pm->triangle[i][0]].z)*2000.0 + 1024.0;
    float y0 = (pm->vertex[pm->triangle[i][0]].y/pm->vertex[pm->triangle[i][0]].z)*-2000.0 + 1024.0;
    float x1 = (pm->vertex[pm->triangle[i][1]].x/pm->vertex[pm->triangle[i][1]].z)*2000.0 + 1024.0;
    float y1 = (pm->vertex[pm->triangle[i][1]].y/pm->vertex[pm->triangle[i][1]].z)*-2000.0 + 1024.0;
    float x2 = (pm->vertex[pm->triangle[i][2]].x/pm->vertex[pm->triangle[i][2]].z)*2000.0 + 1024.0;
    float y2 = (pm->vertex[pm->triangle[i][2]].y/pm->vertex[pm->triangle[i][2]].z)*-2000.0 + 1024.0;

	// generate barycentric co-ords
		/*
		*	calculate plane
		*	get point P by checking intersection of the plane with a triangle
		*
		*	cal w1, w2.
		*	w1 = (Ax(Cy-Ay)+(Py-Ay)(Cx-Ax)-Px(Cy-Ay) / (By-Ay)(Cx-Ax) - (Bx - Ax)(Cy - Ay)
		*	w2 = Py - Ay - w1(By - Ay) / (Cy - Ay)
		*
		*	Point P is inside if w1 >= 0, w2 >= 0, (w1 + w2) <= 1
		*/


    // store these triangles ?

	// Run Ray tracer ?

   }

  // Output the framebuffer.
  fb->writeRGBFile((char *)"test.ppm");

  return 0;

}

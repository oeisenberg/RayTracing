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

void crossProduct(float p_A[], float p_B[], float p_C[]){
  p_C = p_A[1] * p_B[2] - p_A[2] * v_B[1];
  p_C = p_A[0] * p_B[2] - p_A[2] * v_B[0];
  p_C = p_A[0] * p_B[1] - p_A[1] * v_B[0];
}

int main(int argc, char *argv[])
{
  // Create a framebuffer
  FrameBuffer *fb = new FrameBuffer(2048,2048);

  // The following transform allows 4D homogeneous coordinates to be transformed. It moves the supplied teapot model to somewhere visible.
  Transform *transform = new Transform(1.0f, 0.0f, 0.0f, 0.0f,0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 7.0f,0.0f,0.0f,0.0f,1.0f);

  // Read in the teapot model.
  PolyMesh *pm = new PolyMesh((char *)"teapot.ply", transform);

  // Create RayTracer

  // create Camera
  // create a camera class with the required attributes
  
  // For each triangle in the model,
   for (int i = 0; i< pm->triangle_count; i += 1)
  {
    // Calculate Planes
    float point_A = {pm->vertex[pm->triangle[i][0]].x, pm->vertex[pm->triangle[i][0]].y, pm->vertex[pm->triangle[i][0]].z};
    float point_B = {pm->vertex[pm->triangle[i][1]].x, pm->vertex[pm->triangle[i][1]].y, pm->vertex[pm->triangle[i][1]].z};
    float point_C = {pm->vertex[pm->triangle[i][2]].x, pm->vertex[pm->triangle[i][2]].y, pm->vertex[pm->triangle[i][2]].z};

    float AB = point_B - point_A;
    float AC = pointC - point_A;
    float cross = {3};

    crossProduct(point_A, point_B, cross);



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


    // store these triangles ?

	// Run Ray tracer ?

   }

  // Output the framebuffer.
  fb->writeRGBFile((char *)"test.ppm");

  return 0;

}

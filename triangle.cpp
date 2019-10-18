/***************************************************************************
 *
 * krt - Kens Raytracer - Coursework Edition. (C) Copyright 1997-2019.
 *
 * Do what you like with this code as long as you retain this comment.
 */

#include "triangle.h"
#include <math.h>
#include "vector.h"


Triangle::Triangle(Vertex vertex_A, Vertex vertex_B, Vertex vertex_C)
{
	a = vertex_A;
	b = vertex_B;
	c = vertex_C;
}

void Triangle::intersection(Ray ray, Hit &hit)
{
	hit.flag = false;
	float errorValue = 1e-8;

	// Compute Triangle's Normal
	Vector AB = b - a;
	Vector AC = c - a;

	Vector N;
	AB.cross(AC, N);
	// float denom = N.dotProduct(N);

	// Find P
	// Check if Ray is parallel to the triangle's plane
	float NDir = N.dot(ray.direction);
	if (fabs(NDir) < errorValue){
		// Parallel
		// std::cerr << "Parallel" << std::endl;
		return;
	}

	// Converting for use later
	Vector a_Vector = a.convertToVector();
	Vector b_Vector = b.convertToVector();
	Vector c_Vector = c.convertToVector();
	Vector rayPos_Vector = ray.position.convertToVector();

	float d = N.dot(a_Vector);
	// Check if the triangle is behind the ray
	float t = (N.dot(rayPos_Vector) + d) / NDir; //parametric t (for distance)
	// if (t < 0) {
		// triangle behind
	// 	std::cerr << "N: "<< N.x << ", " << N.y << ", " << N.z << std::endl;
	// 	std::cerr << "a: " << a_Vector.x << ", " << a_Vector.y << ", " << a_Vector.z << std::endl;
	// 	std::cerr << "Ray: " << ray.direction.x << ", " << ray.direction.y << ", " << ray.direction.z << std::endl;
	// 	std::cerr << "Behind: " << d << ", " << N.dot(rayPos_Vector) + d << ", " << NDir << std::endl;
		// return;
	// }

	// Calculate intersection point P
	Vector P = rayPos_Vector + ray.direction.multiply(d);

	// Complete Tests:
	Vector A_cross;
	Vector B_cross;
	Vector C;

	// Edge AB test
	// AB = b - a;
	Vector vPa = P - a_Vector;
	AB.cross(vPa, C);
	if (N.dot(C) < 0){
		// P is outside
		// std::cerr << "Failed 1" << std::endl;
		return;
	}

	// Edge BC test
	Vector BC = c - b;
	Vector vPb = P - b_Vector;
	BC.cross(vPb, C);
	if (N.dot(C) < 0) // TO DO: Save the value (u) for colour shading (Lab 4)
	{
		// std::cerr << "Failed 2" << std::endl;
		return;
	}

	// Edge CA test
	Vector CA = a - c;
	Vector vPc = P - c_Vector;
	CA.cross(vPc, C);
	if (N.dot(C) < 0) // TO DO: Save the value (v) for colour shading (Lab 4)
	{
		// std::cerr << "Failed 3" << std::endl;
		return;
	}

	// TO DO: Understand why this is done to get colour values (Lab 4)
	// u /= denom ?
	// v /= denom ?

	hit.what = this;
	hit.normal = N;
	hit.normal.normalise();
	hit.flag = true;
	hit.t = t;
	return;
}

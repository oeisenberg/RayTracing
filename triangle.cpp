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
	// Möller–Trumbore ray-triangle intersection algorithm

	hit.flag = false;
	float errorValue = 1e-8;

	Vector AB = b - a;
	Vector AC = c - a;

	Vector vecP;
	ray.direction.cross(AC, vecP);
	float det = AB.dot(vecP);
	if (fabs(det) < errorValue){
		return;
	}

	float invDet = 1/det;
	Vector triVector = ray.position - a;
	float u = invDet * triVector.dot(vecP);
	if (u < 0 || u > 1)
	{
		return;
	}

	Vector q;
	triVector.cross(AB, q);
	float v = invDet * ray.direction.dot(q);
	if (v < 0 || u + v > 1)
	{
		return;
	}

	float t = invDet * AC.dot(q);

	if (t < 0)
	{
		return;
	}

	Vector P = ray.position.convertToVector() + ray.direction.multiply(t);
	Vector N;
	AB.cross(AC, N);

	// // TO DO: Understand why this is done to get colour values (Lab 4)
	// // u /= denom ?
	// // v /= denom ?

	hit.what = this;
	hit.normal = N;
	hit.normal.normalise();
	hit.position.x = P.x;
	hit.position.y = P.y;
	hit.position.z = P.z;
	hit.flag = true;
	hit.t = t;

	return;
}

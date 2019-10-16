/***************************************************************************
 *
 * krt - Kens Raytracer - Coursework Edition. (C) Copyright 1997-2019.
 *
 * Do what you like with this code as long as you retain this comment.
 */

#include "triangle.h"
#include <math.h>


Triangle::Triangle(Vertex vertex_A, Vertex vertex_B, Vertex vertex_C)
{
	a = vertex_A;
	b = vertex_B;
	c = vertex_C;
}

void Sphere::intersection(Ray ray, Hit &hit)
{
	Vector ro;

	hit.flag = false;

	// offset ray by sphere position
	// equivalent to transforming ray into local sphere space

	ro.x = ray.position.x - center.x;
	ro.y = ray.position.y - center.y;
	ro.z = ray.position.z - center.z;

	return;
}

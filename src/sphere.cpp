/***************************************************************************
 *
 * krt - Kens Raytracer - Coursework Edition. (C) Copyright 1997-2019.
 *
 * Do what you like with this code as long as you retain this comment.
 */

#include <math.h>
#include "sphere.h"
#include "material.h"

// Sphere Constructor
Sphere::Sphere(Vertex c, float r, Material *m)
{
	center = c;
	radius = r;
	objMaterial = m;
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

	float a = (float)ray.direction.dot(ray.direction);
	float b = (float)(2.0 * ray.direction.dot(ro));
	float c = (float)ro.dot(ro) - radius*radius;

	float disc = b*b - 4 * a*c;

	if (disc < 0.0)
	{
		return; // a negative value indicates no intersection.
	}

	float ds = sqrtf(disc);


	float t0 = (-b - ds) / 2.0f;
	float t1 = (-b + ds) / 2.0f;

	if (t1 < 0.0)
	{
		return;
	}

	// if an intersection has been found, record details in hit object

	hit.what = this;

	if (t0 > 0.0) //smallest root is positive.
	{
		hit.t = t0;

		hit.position.x = ray.position.x + t0 * ray.direction.x;
		hit.position.y = ray.position.y + t0 * ray.direction.y;
		hit.position.z = ray.position.z + t0 * ray.direction.z;
		hit.normal.x = hit.position.x - center.x;
		hit.normal.y = hit.position.y - center.y;
		hit.normal.z = hit.position.z - center.z;
		hit.normal.normalise();
		hit.flag = true;

		return;
	}

	hit.t = t1;

	hit.position.x = ray.position.x + t1 * ray.direction.x;
	hit.position.y = ray.position.y + t1 * ray.direction.y;
	hit.position.z = ray.position.z + t1 * ray.direction.z;
	hit.normal.x = hit.position.x - center.x;
	hit.normal.y = hit.position.y - center.y;
	hit.normal.z = hit.position.z - center.z;
	hit.normal.normalise();
	hit.flag = true;

	return;
}

Vertex Sphere::calcSurfacePoint(){
	float min = -radius;
  	float max = radius;
  	float x, y, z, r;
  	do {
		r = (float) rand() / (float) RAND_MAX; x = min + r * (max - min);
		r = (float) rand() / (float) RAND_MAX; y = min + r * (max - min);
		r = (float) rand() / (float) RAND_MAX; z = min + r * (max - min);
  	} while (pow(x,2)+pow(y,2)+pow(z,2)>pow(radius,2));
	return Vertex(center.x+x, center.y+y, center.z+z);
}
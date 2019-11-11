/***************************************************************************
 *
 * ohe21 - Oliver's Triangle Class
 *
 * Do what you like with this code as long as you retain this comment.
 */

#include <math.h>
#include "triangle.h"
#include "vector.h"


Triangle::Triangle(Vertex vertex_A, Vertex vertex_B, Vertex vertex_C, float aC, float dC, float sC, float Red, float Green, float Blue)
{
	a = vertex_A;
	b = vertex_B;
	c = vertex_C;

	R = Red;
	B = Blue;
	G = Green;

	aCoeff = aC;
	dCoeff = dC;
	sCoeff = sC;
}

// Möller–Trumbore ray-triangle intersection algorithm
// https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm
// https://www.scratchapixel.com/code.php?id=9&origin=/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle
void Triangle::intersection(Ray ray, Hit &hit)
{
	hit.flag = false;
	float errorValue = 1e-8;

	Vector AB = b - a;
	Vector AC = c - a;

	Vector vecP;
	ray.direction.cross(AC, vecP);

	float det = AB.dot(vecP);
	if (fabs(det) < errorValue){
		// negative means that the triangle is facing away.
		// close to 0 means that the ray misses the triangle
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
		// Triangle is behind the camera
		return;
	}

	Vector P = ray.position.convertToVector() + ray.direction.multiply(t);
	Vector N;
	AB.cross(AC, N);

	hit.what = this;
	hit.normal = N;
	hit.normal.normalise();
	hit.position.x = P.x;
	hit.position.y = P.y;
	hit.position.z = P.z;
	hit.u = u;
	hit.v = v;
	hit.flag = true;
	hit.t = t;

	return;
}

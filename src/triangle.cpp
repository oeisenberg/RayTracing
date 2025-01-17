/***************************************************************************
 *
 * ohe21 - Oliver's Triangle Class
 *
 */

#include <math.h>
#include "triangle.h"
#include "vector.h"


Triangle::Triangle(Vertex vertex_A, Vertex vertex_B, Vertex vertex_C, Material *m)
{
	a = vertex_A;
	b = vertex_B;
	c = vertex_C;

	objMaterial = m;
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
	AC.cross(AB, N); 	// Normally AB.cross(AC, N) but the normals seem to be inverted for the smaller teapot

	// Smooth shading
	// calculate avg normal at each vertex (using connectivity info for surrounding faces)
	// baracentric coordinates to use the three normals on the interior of the triangle

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

Vertex Triangle::calcSurfacePoint(){
	int min = -1;
  	int max = 1;
	float x, y, z, r;
	r = (float) rand() / (float) RAND_MAX; x = min + r * (max - min);
	r = (float) rand() / (float) RAND_MAX; y = min + r * (max - min);
	r = (float) rand() / (float) RAND_MAX; z = min + r * (max - min);
	return Vertex(a.x+x, a.y+y, a.z+z);
}

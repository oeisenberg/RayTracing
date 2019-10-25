/***************************************************************************
 *
 * 
 */

#include <math.h>
#include "teapot.h"
#include "polymesh.h"
#include "vertex.h"
#include "scene.h"

Teapot::Teapot(Scene *s, Vertex c)
{
	PolyMesh *pm = new PolyMesh((char *)"teapot.ply", s->t);
	center = c;
}

void Teapot::intersection(Ray ray, Hit &hit)
{
	Vector ro;

	hit.flag = false;

	ro.x = ray.position.x - center.x;
	ro.y = ray.position.y - center.y;
	ro.z = ray.position.z - center.z;

	// check if ray is intersecting with the plane (& parallel)
}
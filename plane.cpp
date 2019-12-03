/***************************************************************************
 *
 * ohe21 - Oliver's Plane class
 *
 */

#include "plane.h"

Plane::Plane(Vertex position, Vector up, Material *m){
  this->position = position;
  up.normalise();
  this->up = up;
	objMaterial = m;
}

void Plane::intersection(Ray ray, Hit &hit)
{
  hit.flag = false;

  //https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-plane-and-ray-disk-intersection

  float denom = ray.direction.dot(up);

  // Check if ray is parallel
  if (fabs(denom) < 1e-5) return ;  // 0 means that the ray is parallel to the plane or that the ray is contained within the plane

  Vector lightToPointOnPlane = this->position - ray.position;
  float t = up.dot(lightToPointOnPlane)/denom;

  if (t < 0.0) return;

  hit.t = t;
  hit.what = this;
  hit.normal = up;
  hit.normal.normalise();
  hit.position.x = ray.position.x + t * ray.direction.x;
  hit.position.y = ray.position.y + t * ray.direction.y;
  hit.position.z = ray.position.z + t * ray.direction.z;
  hit.flag = true;

  return;
}

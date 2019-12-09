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

Vertex Plane::calcSurfacePoint(){
	int min = -10;
  int max = 10;
  float a, b, r;
  r = (float) rand() / (float) RAND_MAX; a = min + r * (max - min);
  r = (float) rand() / (float) RAND_MAX; b = min + r * (max - min);

  if (up.x == 1){
    return Vertex(1, a, b);
  } else if (up.y == 1){
    return Vertex(a, 1, b);
  } else if  (up.z == 1){
    return Vertex(a, b, 1);
  } else {
    // Throw exception?
    std::cout << "Plane.cpp ln 59: What is up?" << std::endl;
    return Vertex(0,0,0);
  }
}
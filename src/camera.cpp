#include <iostream>
#include "camera.h"
#include "vector.h"
#include "vertex.h"
#include "ray.h"
#include "scene.h"

// Using the given camera model from the slides
// FOV is in RAD
Camera::Camera(Vertex Eye, Vertex Look, Vector Up, float D, float FOV){
  this->e = Eye;
  this->l = Look;
  this->u = Up;
  this->d = D;
  this->FOV = FOV;

  Vector el = Eye - Look;
  Vector uw = Vector(0, 0, 0);
  Vector wu = Vector(0, 0, 0);

  el.normalise();
  this->w = el;

  Up.cross(this->w, uw);
  uw.normalise();
  this->u = uw;

  this->w.cross(this->u, wu);
  this->v = wu;
}

// Ray calculation taken from the slides
Ray Camera::getRay(Scene *sc, int x, int y)
{
  float Rx = (tan(this->FOV)/2) * (sc->width/2 - x + 0.5);
  float Ry = (tan(this->FOV)/2) * (sc->height/2 - y + 0.5);

  Vector Dir = this->u.multiply(Rx) + (this->v.multiply(Ry)) - (this->w.multiply(this->d));
  Dir.normalise();

  return Ray(this->e, Dir);
}
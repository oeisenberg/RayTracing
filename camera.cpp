#include <iostream>
#include "camera.h"
#include "vector.h"
#include "vertex.h"
#include <math.h>

Camera::Camera(Vertex Eye, Vertex Look, Vector Up, float D){
  this->e = Eye;
  this->l = Look;
  this->u = Up;
  this->d = D;

  Vector el = Vector(Eye.x - Look.x, Eye.y - Look.y, Eye.z - Look.z);
  // Vector el = Eye - Look; // Overloading ?
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

/***************************************************************************
*
* ohe - Oliver's Light Class
*/

#pragma once

#include "vertex.h"
#include "vector.h"

class Light {
  float intensity;
  Vertex position;
  Vector direction;

  public:
    Light(float i);
    Light(float i, Vector *dir);
    Light(float i, Vertex p);
    Light(float i, Vertex p, Vector *dir);
};

/***************************************************************************
 *
 *
 */

#pragma once

#include "light.h"
#include <vector>

class Spotlight : public Light {
public:
  // Spotlight(Colour of the light, light ray emittion direction)
  Spotlight(Colour i, Vector *dir);
  Colour getIntensity();
  Vector getDirection();
  Vertex getPosition();
  float getDistance(Vertex pointA);
  Vector getRandEmittionDirection();
  Vertex getRandEmittionPosition();
};

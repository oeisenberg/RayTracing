/***************************************************************************
 *
 * Oliver's Pointlight class
 *
 * Assuming a point light does NOT have a direction.
 * Therefore intensity is constant.
 */

#pragma once

#include "light.h"

class Pointlight : public Light {
public:
  Pointlight(Colour i, Vertex *Position);
  Colour getIntensity();
  Vector getDirection();
  Vector getDirection(Vertex hitPos);
  Vector getRandEmittionDirection();
  Vertex getRandEmittionPosition();
  Vertex getPosition();
  float getDistance(Vertex pointA);
};

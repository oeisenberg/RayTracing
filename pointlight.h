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
  //float falloff;

  Pointlight(float i, Vertex *Position);
  //Pointlight(float i, Vertex Position, Vector dir)
  float getIntensity();
  Vector getDirection();
  Vector getDirection(Vertex hitPos);
  Vertex getPosition();
};

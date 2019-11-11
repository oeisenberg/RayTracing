/***************************************************************************
 *
 * Oliver's Pointlight class
 */

#pragma once

#include "light.h"

class Pointlight : public Light {
public:
  float falloff;

  Pointlight(float i, Vertex Position);
  Pointlight(float i, Vertex Position, Vector dir)
  float getIntensity();
  Vector getDirection();
  Vertex getPosition();
};

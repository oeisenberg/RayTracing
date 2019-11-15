/***************************************************************************
 *
 *
 */

#pragma once

#include "light.h"
#include <vector>

class Spotlight : public Light {
public:
  Spotlight(float i, Vector *dir);
  float getIntensity();
  Vector getDirection();
  Vertex getPosition();
  float getDistance(Vertex pointA);
};

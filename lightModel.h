/***************************************************************************
 *
 *
 */

// Object is the base class for objects.
#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "vector.h"
#include "light.h"
#include <vector>

class LightModel {
public:
  Vector lightDirection; // TODO: change to vector of lights
  std::vector<Light> lights;

  virtual float getCoeff()
  {

  }

};

#endif

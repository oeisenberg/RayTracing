/***************************************************************************
 *
 *
 */

// Object is the base class for objects.
#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "vector.h"

class Light {
public:
  Vector lightDirection; // TODO: change to vector of lights 

  virtual float getCoeff()
  {

  }

};

#endif

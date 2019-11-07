/***************************************************************************
 *
 *  ohe21 - Oliver's light class
 */

// LIGHT is the base class for objects.
#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "vector.h"
#include "vertex.h"
#include <vector>

class Light {
protected:
  float intensity;
  Vertex position;
  Vector direction;
public:
  virtual float getIntensity(){
  };
  
  virtual Vector getDirection(){
  };

  virtual Vertex getPosition(){
  };
};

#endif

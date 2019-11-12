/***************************************************************************
 *
 *  ohe21 - Oliver's light class
 */

// LIGHT is the base class for objects.
#ifndef _LIGHT_H_
#define _LIGHT_H_

#include <stdexcept>
#include <vector>
#include "vector.h"
#include "vertex.h"

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

  virtual Vector getDirection(Vertex){
  };

  virtual float getDistance(Vertex){
  };

};

// TODO: how to show a light source?

#endif

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
#include "colour.h"
#include "vertex.h"
#include "object.h"

class Light {
protected:
  Colour intensity;
  Vertex position;
  Vector direction;
public:
  // Returns the light's colour
  virtual Colour getIntensity(){
  };

  // Returns the light's direction
  virtual Vector getDirection(){
  };

  // Returns the lights position
  virtual Vertex getPosition(){
  };

  // Allows support for light sources with no direction as it can be computed dynamically
  virtual Vector getDirection(Vertex){
  };

  virtual float getDistance(Vertex){
  };

  virtual Vector getRandEmittionDirection(){
  };

  virtual Vertex getRandEmittionPosition(){
  };

  float getStrength(){
    return intensity.getStrength();
  };

};

// TODO: how to show a light source?

#endif

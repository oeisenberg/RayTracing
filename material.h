/***************************************************************************
 *
 * ohe21 - Oliver's Material Class
 *
 */

#pragma once

#include "colour.h"

class Material {
  float ambeintValue;
  float diffuseValue;
  float specularValue;
  // Could be updated to hold information about texture in a future update.
  Colour *colour;
  float reflectiveValue;
  float transparentValue;

public:
  Material(Colour *colour, float ambientVal, float diffVal, float specVal);
  Material(Colour *colour, float ambientVal, float diffVal, float specVal, float reflectiveValue, float transparentValue);
  float getAmbientValue();
  float getDiffuseValue();
  float getSpecularValue();
  Colour *getColour();
};

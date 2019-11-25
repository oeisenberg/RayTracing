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
  // Could be updated to hold information about colour and texture in a future update.
  Colour *colour;
  bool isReflective = false;
  bool isTransparant = false;

public:
  Material(Colour *colour, float ambientVal, float diffVal, float specVal);
  Material(Colour *colour, float ambientVal, float diffVal, float specVal, bool isReflective, bool isTransparant);
  float getAmbientValue();
  float getDiffuseValue();
  float getSpecularValue();
  Colour *getColour();
};

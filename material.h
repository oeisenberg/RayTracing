/***************************************************************************
 *
 * ohe21 - Oliver's Material Class
 *
 */

#pragma once

#include "colour.h"

class Material {
  Colour *ambeint;
  Colour *diffuse;
  Colour *specular;
  float  power;

  // Could be updated to hold information about texture in a future update.
  Colour *colour;
  float reflectiveValue;
  float transparentValue;

public:
  Material(Colour *colour, Colour *ambientVal, Colour *diffuseVal, Colour *specularVal);
  Material(Colour *colour, Colour *ambientVal, Colour *diffVal, Colour *specVal, float reflectiveValue, float transparentValue);
  Colour getAmbientValue();
  Colour getDiffuseValue();
  Colour getSpecularValue();
  Colour *getColour();

  void computeBaseColour();
  Colour compute_light_colour();
};

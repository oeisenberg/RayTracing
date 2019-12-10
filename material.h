/***************************************************************************
 *
 * ohe21 - Oliver's Material Class
 *
 */

#pragma once

#include "colour.h"
#include "vector.h"

class Material {
public:
  Colour diffuse;
  Colour specular;
  float  power;

  // Could be updated to hold information about texture in a future update.
  Colour colour;


  bool isReflective = false;
  Colour reflectionDegree;
  bool isTransparent = false;
  Colour transparentDegree;
  float ior = 1; 	// Index of refraction Vacuum: 1.0, Air: 1.003, Water: 1.33, Glass 1.52

  Material(Colour colour, Colour diffuseVal, Colour specularVal, float power);
  Material(Colour colour, Colour diffVal, Colour specVal, float power, Colour reflectionDegree);
  Material(Colour colour, Colour diffVal, Colour specVal, float power,  Colour reflectionDegree, Colour transparentDegree, float ior);
  Colour getAmbientValue();
  Colour getDiffuseValue();
  Colour getSpecularValue();
  Colour getColour();

  Colour computeBaseColour();
  Colour compute_light_colour(Vector SurfaceNormal, Vector viewer, Vector lightDir, float diff);
};

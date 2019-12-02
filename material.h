/***************************************************************************
 *
 * ohe21 - Oliver's Material Class
 *
 */

#pragma once

#include "colour.h"
#include "vector.h"

class Material {
  Colour ambeint;
  Colour diffuse;
  Colour specular;
  float  power;

  // Could be updated to hold information about texture in a future update.
  Colour colour;

public:
  bool isReflective;
  float refectionDegree;
  bool isTransparent;
  float transparentDegree;
  float ior; 	// Index of refraction Vacuum: 1.0, Air: 1.003, Water: 1.33, Glass 1.52

  Material(Colour colour, Colour ambientVal, Colour diffuseVal, Colour specularVal, float power);
  Material(Colour colour, Colour ambientVal, Colour diffVal, Colour specVal, float power, bool isReflective, float ior);
  Colour getAmbientValue();
  Colour getDiffuseValue();
  Colour getSpecularValue();
  Colour getColour();

  Colour computeBaseColour();
  Colour compute_light_colour(Vector SurfaceNormal, Vector viewer, Vector lightDir, float diff);
};

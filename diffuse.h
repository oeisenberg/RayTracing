/***************************************************************************
*
* ohe - Oliver's Diffuse Lighting Model
*/

#pragma once

#include "light.h"
#include "vector.h"

class Diffuse : public Light {
  float I_diffuse; // Intensity of ambient light
  float K_diffuse; // Surface Diffuse coefficient TODO: Make it a property of the object
  Vector lightDirection;

  public:
    Diffuse(float I_diffuse, float K_diffuse, Vector lightDir);
    float getCoeff(Vector SurfaceNormal);
};

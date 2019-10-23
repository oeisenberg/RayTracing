/***************************************************************************
*
* ohe - Oliver's Diffuse Lighting Model
*/

#pragma once

#include "light.h"
#include "vector.h"

class Diffuse : public Light {
  float I_diffuse; // Intensity of diffuse light
  Vector lightDirection;

  public:
    Diffuse(float I_diffuse, Vector lightDir);
    float getCoeff(Vector SurfaceNormal, float K_diffuse);
};

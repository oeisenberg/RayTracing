/***************************************************************************
*
* ohe - Oliver's Diffuse Lighting Model
*/

#pragma once

#include "lightModel.h"
#include "vector.h"

class Diffuse : public LightModel {
  float I_diffuse; // Intensity of diffuse light

  public:
    Diffuse(float I_diffuse, Vector *lightDir);
    float getCoeff(Vector SurfaceNormal, float K_diffuse);
};

/***************************************************************************
*
* ohe - Oliver's Ambient Lighting Model
*/

#pragma once

#include "lightModel.h"

class Ambient : public Light {
  float I_ambient; // Intensity of ambient light
  float K_ambient; // Ambient Reflection coefficient

  public:
    Ambient(float iA, float kA);
    float getCoeff();
};

/***************************************************************************
*
* ohe - Oliver's Phong Lighting Model
*/

#pragma once

#include "light.h"

class Phong : public Light {
  float I_phong; // Intensity of phong light
  int floatDistribution;

  public:
    Phong();
    float getCoeff();
};

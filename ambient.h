/***************************************************************************
*
* ohe - Oliver's Ambient Lighting Model
*/

#pragma once

#include "lightModel.h"

class Ambient : public LightModel {
  float I_ambient;

  public:
    Ambient(float intensity);
    float getCoeff(float K_ambient);
};

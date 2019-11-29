/***************************************************************************
*
* ohe - Oliver's Ambient Lighting Model
*/

#pragma once

#include "lightModel.h"

class Ambient : public LightModel {
  Colour *I_ambient;

  public:
    Ambient(Colour *intensity);
    Colour getCoeff(float K_ambient);
};

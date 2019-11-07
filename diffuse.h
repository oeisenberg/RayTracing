/***************************************************************************
*
* ohe - Oliver's Diffuse Lighting Model
*
*/

#pragma once

#include "lightModel.h"
#include "vector.h"
#include "light.h"

class Diffuse : public LightModel {
  public:
    Diffuse();
    float getCoeff(std::vector<Light*> lights, Vector SurfaceNormal, float K_diffuse);
};

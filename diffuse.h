/***************************************************************************
*
* ohe21 - Oliver's Diffuse Lighting Model
*
*/

#pragma once

#include "lightModel.h"
#include "vector.h"
#include "light.h"
#include "hit.h"

class Diffuse : public LightModel {
  public:
    Diffuse();
    float getCoeff(std::vector<Light*> lights, Hit hitObj, float K_diffuse);
    Vector getLightDir(std::vector<Light*> lights, int iLight, Hit hitObj);
};

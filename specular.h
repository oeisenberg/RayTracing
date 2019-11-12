/***************************************************************************
*
* ohe - Oliver's Specular Lighting Model
*/

#pragma once

#include "lightModel.h"
#include "vertex.h"
#include "light.h"
#include "hit.h"

class Specular : public LightModel {
  int distribution;

  public:
    Specular(int distribution);
    float getCoeff(std::vector<Light*> lights, std::vector<Object*> objs, Hit hitObj, Vertex camEye, float sCoeff);
    Vector getLightDir(std::vector<Light*> lights, int iLight, Hit hitObj);
};

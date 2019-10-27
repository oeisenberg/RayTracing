/***************************************************************************
*
* ohe - Oliver's Specular Lighting Model
*/

#pragma once

#include "lightModel.h"
#include "vertex.h"
#include "light.h"

class Specular : public LightModel {
  int distribution;

  public:
    Specular(int distribution);
    float getCoeff(std::vector<Light*> lights, Vector SurfaceNormal, Vertex camEye, Vertex hitPos, float sCoeff);
};

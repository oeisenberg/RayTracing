/***************************************************************************
*
* ohe - Oliver's Specular Lighting Model
*/

#pragma once

#include "lightModel.h"
#include "vertex.h"

class Specular : public Light {
  float I_specular; // Intensity of phong light
  int distribution;

  public:
    Specular(float I_specular, int distribution, Vector *lightDir);
    float getCoeff(Vector SurfaceNormal, Vertex camEye, Vertex hitPos);
};

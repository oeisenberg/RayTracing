/***************************************************************************
*
* ohe - Oliver's Phong Lighting Model
*/

#pragma once

#include "lightModel.h"
#include "vertex.h"

class Phong : public Light {
  float I_phong; // Intensity of phong light
  int distribution;

  public:
    Phong(float I_phong, int distribution, Vector *lightDir);
    float getCoeff(Vector SurfaceNormal, Vertex camEye, Vertex hitPos);
};

/***************************************************************************
*
* ohe - Oliver's Specular Lighting Model
*/

#pragma once

#include "lightModel.h"
#include "vertex.h"

class Specular : public Light {
<<<<<<< HEAD:specular.h
  float I_specular; // Intensity of specular light 
=======
  float I_specular; // Intensity of phong light
>>>>>>> 74f4d1849ddf9161c94edef4a4e3f3ce1902e082:specular.h
  int distribution;

  public:
    Specular(float I_specular, int distribution, Vector *lightDir);
    float getCoeff(Vector SurfaceNormal, Vertex camEye, Vertex hitPos);
};

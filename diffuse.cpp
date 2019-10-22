#include "diffuse.h"
#include "vector.h"

Diffuse::Diffuse(float iD, float kD, Vector lightDir)
{
  I_diffuse = iD;
  K_diffuse = kD;
  lightDirection = lightDir;
}

float Diffuse::getCoeff(Vector SurfaceNormal)
{
  return I_diffuse * K_diffuse * SurfaceNormal.dot(lightDirection);
}

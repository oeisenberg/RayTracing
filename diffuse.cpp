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
  float normalCoeff = SurfaceNormal.dot(lightDirection);

  if (normalCoeff < 0) return 0; // Removes negative normalCoeff values

  return I_diffuse * K_diffuse * normalCoeff;
}

#include "diffuse.h"
#include "vector.h"

Diffuse::Diffuse(float iD, Vector lightDir)
{
  I_diffuse = iD;
  lightDirection = lightDir.multiply(-1);
}

float Diffuse::getCoeff(Vector SurfaceNormal, float K_diffuse)
{
  float normalCoeff = SurfaceNormal.dot(lightDirection);

  if (normalCoeff < 0) return 0; // Removes negative normalCoeff values

  return I_diffuse * K_diffuse * normalCoeff;
}

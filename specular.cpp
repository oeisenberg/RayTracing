/***************************************************************************
*
* ohe - Oliver's Specular Lighting Model
*/

#include "specular.h"

Specular::Specular(float intensity, int n, Vector *lightDir)
{
  I_specular = intensity;
  distribution = n;
  lightDirection = *lightDir;
}

float Specular::getCoeff(Vector SurfaceNormal, Vertex camEye, Vertex hitPos)
{
  float normalCoeff = SurfaceNormal.dot(lightDirection);

  Vector Reflection;
  SurfaceNormal.reflection(lightDirection, Reflection);

  Vector viewerDirection = camEye - hitPos;
  viewerDirection.normalise();

  float specularCoeff = Reflection.dot(viewerDirection);

  if (specularCoeff < 0) return 0;

  return I_specular * 1 * pow(specularCoeff, distribution);
}

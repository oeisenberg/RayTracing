#include "phong.h"

Phong::Phong(float intensity, int n, Vector *lightDir)
{
  I_phong = intensity;
  distribution = n;
  lightDirection = *lightDir;
}

float Phong::getCoeff(Vector SurfaceNormal, Vertex camEye, Vertex hitPos)
{
  float normalCoeff = SurfaceNormal.dot(lightDirection);

  Vector Reflection;
  SurfaceNormal.reflection(lightDirection, Reflection);

  Vector viewerDirection = camEye - hitPos;
  viewerDirection.normalise();

  float specularCoeff = Reflection.dot(viewerDirection);

  if (specularCoeff < 0) return 0;

  return I_phong * 1 * pow(specularCoeff, distribution);
}

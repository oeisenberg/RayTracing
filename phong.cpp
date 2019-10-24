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

  if (normalCoeff < 0) return 0; // Removes negative normalCoeff values

  Vector R = lightDirection - (SurfaceNormal.multiply(2 * normalCoeff));
  Vector viewerDirection = camEye - hitPos;
  viewerDirection.normalise();

  float specularCoeff = R.dot(viewerDirection);

  // if (specularCoeff < 0) return 0;

  return I_phong * 0.4 * pow(specularCoeff, distribution);
}

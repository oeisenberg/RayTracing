/***************************************************************************
*
* ohe - Oliver's Specular Lighting Model
*/

#include "specular.h"
#include "light.h"

Specular::Specular(int n)
{
  distribution = n;
}

float Specular::getCoeff(std::vector<Light*> lights, Vector SurfaceNormal, Vertex camEye, Vertex hitPos, float sCoeff)
{
  float sCoeffs = 0.0;
  Vector viewerDirection = camEye - hitPos;
  viewerDirection.normalise();

  for (float iLight = 0; iLight < lights.size(); iLight++){
    Vector lightDirection = lights[iLight]->getDirection().multiply(-1);
    float normalCoeff = SurfaceNormal.dot(lightDirection);

    Vector Reflection;
    SurfaceNormal.reflection(lightDirection, Reflection);

    float specularCoeff = Reflection.dot(viewerDirection);

    if (specularCoeff > 0) {
      float intensity = lights[iLight]->getIntensity();
      sCoeffs += (intensity * sCoeff * pow(specularCoeff, distribution));
    }
  }

  return sCoeffs;
}

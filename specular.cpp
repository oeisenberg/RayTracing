/***************************************************************************
*
* ohe - Oliver's Specular Lighting Model
*/

#include "specular.h"
#include "light.h"
#include "hit.h"

Specular::Specular(int n)
{
  distribution = n;
}

float Specular::getCoeff(std::vector<Light*> lights, Hit hitObj, Vertex camEye, float sCoeff)
{
  Vector SurfaceNormal = hitObj.normal;
  float sCoeffs = 0.0;
  Vector viewerDirection = camEye - hitObj.position;
  viewerDirection.normalise();

  for (float iLight = 0; iLight < lights.size(); iLight++){
    Vector lightDirection = getLightDir(lights, iLight, hitObj);

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

Vector Specular::getLightDir(std::vector<Light*> lights, int iLight, Hit hitObj){
  Vector lightDir;
  try{
    lightDir = lights[iLight]->getDirection().multiply(-1);
  } catch(const std::exception e){
    lightDir = lights[iLight]->getDirection(hitObj.position).multiply(-1);
  }
  return lightDir;
}

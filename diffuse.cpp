/***************************************************************************
*
* ohe21 - Oliver's Diffuse Lighting Model
*
*/

#include <stdexcept>
#include "diffuse.h"
#include "vector.h"
#include "light.h"
#include "hit.h"

Diffuse::Diffuse()
{

}

// Caclulates the total diffuse coefficient for the pxiel
float Diffuse::getCoeff(std::vector<Light*> lights, Hit hitObj, float K_diffuse)
{
  Vector SurfaceNormal = hitObj.normal;
  float dCoeffs = 0.0;
  for (float iLight = 0; iLight < lights.size(); iLight++){
    Vector lightDir = getLightDir(lights, iLight, hitObj);
    float normalCoeff = SurfaceNormal.dot(lightDir);

    if (normalCoeff > 0){
      float intensity = lights[iLight]->getIntensity();
      dCoeffs += (intensity * K_diffuse * normalCoeff);
    }
  }
  return dCoeffs;
}

Vector Diffuse::getLightDir(std::vector<Light*> lights, int iLight, Hit hitObj){
  Vector lightDir;
  try{
    lightDir = lights[iLight]->getDirection();
  } catch(const std::exception e){
    lightDir = lights[iLight]->getDirection(hitObj.position);
  }
  return lightDir;
}

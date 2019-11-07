/***************************************************************************
*
* ohe21 - Oliver's Diffuse Lighting Model
*
*/

#include "diffuse.h"
#include "vector.h"
#include "light.h"

Diffuse::Diffuse()
{

}

// Caclulates the total diffuse coefficient for the pxiel
float Diffuse::getCoeff(std::vector<Light*> lights, Vector SurfaceNormal, float K_diffuse)
{
  float dCoeffs = 0.0;
  for (float iLight = 0; iLight < lights.size(); iLight++){
    Vector lightDir = lights[iLight]->getDirection();
    float normalCoeff = SurfaceNormal.dot(lightDir);

    if (normalCoeff > 0){
      float intensity = lights[iLight]->getIntensity();
      dCoeffs += (intensity * K_diffuse * normalCoeff);
    }
  }
  return dCoeffs;
}

/***************************************************************************
 *
 * ohe21 - Oliver's Material Class
 *
 */

#include "material.h"

Material::Material(Colour *colour, Colour *ambientVal, Colour *diffVal, Colour *specVal)
{
  this->colour = colour;

  this->ambeint = ambientVal;
  this->diffuse = diffVal;
  this->specular = specVal;

  this->reflectiveValue = 0;
  this->transparentValue = 0;
}

Material::Material(Colour *colour, Colour *ambientVal, Colour *diffVal, Colour *specVal, float reflectiveValue, float transparentValue)
{
  this->colour = colour;

  this->ambeint = ambientVal;
  this->diffuse = diffVal;
  this->specular = specVal;

  this->reflectiveValue = reflectiveValue;
  this->transparentValue = transparentValue;
}

Colour *Material::getColour(){
  return this->colour;
}

void computeBaseColour(){

}

void compute_light_colour(){
  // Vector SurfaceNormal = hitObj.normal;
  // Colour dCoeffs;
  // for (float iLight = 0; iLight < lights.size(); iLight++){
  //   Vector lightDir = getLightDir(lights, iLight, hitObj);
  //   float normalCoeff = SurfaceNormal.dot(lightDir);
  //
  //   if (normalCoeff > 0){
  //     Colour intensity = lights[iLight]->getIntensity();
  //     Ray ray = Ray(hitObj.position + lightDir.multiply(1), lightDir);
  //     if (!checkForShadow(hitObj, objs, ray, lights[iLight])){
  //       dCoeffs += (intensity * K_diffuse * normalCoeff);
  //     }
  //   }
  // }

  // return ambeint; // temp
}

// Vector Diffuse::getLightDir(std::vector<Light*> lights, int iLight, Hit hitObj){
//   Vector lightDir;
//   try{
//     lightDir = lights[iLight]->getDirection();
//   } catch(const std::exception e){
//     lightDir = lights[iLight]->getDirection(hitObj.position);
//   }
//   return lightDir;
// }

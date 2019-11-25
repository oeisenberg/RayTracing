/***************************************************************************
 *
 * ohe21 - Oliver's Material Class
 *
 */

#include "material.h"

Material::Material(Colour *colour, float ambientVal, float diffVal, float specVal)
{
  this->colour = colour;

  this->ambeintValue = ambientVal;
  this->diffuseValue = diffVal;
  this->specularValue = specVal;
}

Material::Material(Colour *colour, float ambientVal, float diffVal, float specVal, bool isReflective, bool isTransparant)
{
  this->colour = colour;

  this->ambeintValue = ambientVal;
  this->diffuseValue = diffVal;
  this->specularValue = specVal;

  this->isReflective = isReflective;
  if (!isReflective && isTransparant){
    this->isTransparant = isTransparant;
  } else {
    this->isTransparant = false;
  }

}

float Material::getAmbientValue(){
  return this->ambeintValue;
}

float Material::getDiffuseValue(){
  return this->diffuseValue;
}

float Material::getSpecularValue(){
  return this->specularValue;
}

Colour *Material::getColour(){
  return this->colour;
}

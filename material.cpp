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

  this->reflectiveValue = 0;
  this->transparentValue = 0;
}

Material::Material(Colour *colour, float ambientVal, float diffVal, float specVal, float reflectiveValue, float transparentValue)
{
  this->colour = colour;

  this->ambeintValue = ambientVal;
  this->diffuseValue = diffVal;
  this->specularValue = specVal;

  this->reflectiveValue = reflectiveValue;
  this->transparentValue = transparentValue;
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

/***************************************************************************
 *
 * ohe21 - Oliver's Material Class
 *
 */

#pragma once

#include "material.h"

Material::Material(float ambientVal, float diffVal, float specVal)
{
  this->ambeintValue = ambientVal;
  this->diffuseValue = diffVal;
  this->specularValue = specVal;
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

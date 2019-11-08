/***************************************************************************
 *
 * ohe21 - Oliver's Material Class
 *
 */

#pragma once

class Material {
  float ambeintValue;
  float diffuseValue;
  float specularValue;
  // float colour[3]; // std::vector<int> v; ?

public:
  Material(float ambientVal, float diffVal, float specVal)
  {
    this->ambeintValue = ambientVal;
    this->diffuseValue = diffVal;
    this->specularValue = specVal;
  }
  float getAmbientValue(){
    return this->ambeintValue;
  }

  float getDiffuseValue(){
    return this->diffuseValue;
  }

  float getSpecularValue(){
    return this->specularValue;
  }
};

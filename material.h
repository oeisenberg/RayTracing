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
  // Could be updated to hold information about colour and texture in a future update.
  float colour[3];   // float colour[3]; // std::vector<int> v; ?

public:
  Material(float ambientVal, float diffVal, float specVal);
  float getAmbientValue();
  float getDiffuseValue();
  float getSpecularValue();
};

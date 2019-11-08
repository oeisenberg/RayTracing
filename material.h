/***************************************************************************
 *
 * ohe21 - Oliver's Material Class
 *
 */

// Material is the base class for objects.
#ifndef _MATERIAL_H_
#define _MATERIAL_H_

class Material {
public:
  float ambeintValue;
  float diffuseValue;
  float specularValue;
  float colour[3];   // float colour[3]; // std::vector<int> v; ?

  Material(float ambientVal, float diffVal, float specVal);
  virtual float getAmbientValue(){};
  virtual float getDiffuseValue(){};
  virtual float getSpecularValue(){};
};

#endif

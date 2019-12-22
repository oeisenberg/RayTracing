/***************************************************************************
 *
 * ohe21 - Oliver's Material Class
 *
 */

#include "material.h"

Material::Material(Colour col, Colour diffVal, Colour specVal, float power)
{
  colour = col;

  diffuse = diffVal;
  specular = specVal;
  this->power = power;
}

Material::Material(Colour colour, Colour diffVal, Colour specVal, float power, Colour reflectionDegree)
{
  this->colour = colour;

  this->diffuse = diffVal;
  this->specular = specVal;
  this->power = power;

  if (reflectionDegree != 0){
    this->isReflective = true;
    this->reflectionDegree = reflectionDegree;
  }
}

Material::Material(Colour colour, Colour diffVal, Colour specVal, float power, Colour reflectionDegree, Colour transparentDegree, float ior)
{
  this->colour = colour;

  this->diffuse = diffVal;
  this->specular = specVal;
  this->power = power;

  if (reflectionDegree != 0){
    this->isReflective = true;
    this->reflectionDegree = reflectionDegree;
  }

  if (transparentDegree != 0){
    this->isTransparent = true;
    this->transparentDegree = transparentDegree;
    this->ior = ior;
  }

}

Material::Material(Colour colour, Colour diffVal, Colour specVal, float power, Colour reflectionDegree, Colour transparentDegree, float ior, float roughness)
{
  this->colour = colour;

  this->diffuse = diffVal;
  this->specular = specVal;
  this->power = power;

  if (reflectionDegree != 0){
    this->isReflective = true;
    this->reflectionDegree = reflectionDegree;
  }

  if (transparentDegree != 0){
    this->isTransparent = true;
    this->transparentDegree = transparentDegree;
    this->ior = ior;
  }

}

Colour Material::getColour(){
  return this->colour;
}

Colour Material::getDiffuseValue()
{
  return diffuse;
}

Colour Material::getSpecularValue()
{
  return specular;
}

Colour Material::computeBaseColour(){
  return this->colour;
}

Colour Material::compute_light_colour(Vector SurfaceNormal, Vector toViewer, Vector lightDir, float diff){
  lightDir.negate();
  toViewer.normalise();

  Colour result;
  result += diffuse * diff;

  Vector r;
  SurfaceNormal.reflection(lightDir, r);
  r.normalise();
  float specularCoeff = r.dot(toViewer);

    if (specularCoeff > 0.0f) {
      float p = (float)pow(specularCoeff, 20);
      result += specular * p;
  }

  return result;
}
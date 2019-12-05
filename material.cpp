/***************************************************************************
 *
 * ohe21 - Oliver's Material Class
 *
 */

#include "material.h"

Material::Material(Colour col, Colour ambientVal, Colour diffVal, Colour specVal, float power)
{
  colour = col;

  ambeint = ambientVal;
  diffuse = diffVal;
  specular = specVal;
  this->power = power;
}

Material::Material(Colour colour, Colour ambientVal, Colour diffVal, Colour specVal, float power, float reflectionDegree)
{
  this->colour = colour;

  this->ambeint = ambientVal;
  this->diffuse = diffVal;
  this->specular = specVal;
  this->power = power;

  if (reflectionDegree != 0){
    this->isReflective = true;
    this->reflectionDegree = reflectionDegree;
  }
}

Material::Material(Colour colour, Colour ambientVal, Colour diffVal, Colour specVal, float power, float reflectionDegree, float transparentDegree, float ior)
{
  this->colour = colour;

  this->ambeint = ambientVal;
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

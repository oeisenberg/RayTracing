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

  this->isReflective = false;
  this->isTransparent = false;
}

Material::Material(Colour colour, Colour ambientVal, Colour diffVal, Colour specVal, float power, bool reflectiveValue, bool transparentValue)
{
  this->colour = colour;

  this->ambeint = ambientVal;
  this->diffuse = diffVal;
  this->specular = specVal;
  this->power = power;

  this->isReflective = reflectiveValue;
  this->isTransparent = transparentValue;
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
  // toViewer.negate();

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

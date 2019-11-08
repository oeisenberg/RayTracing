#include "spotlight.h"

Spotlight::Spotlight(float i, Vector *dir)
{
  dir->negate();
  dir->normalise();
  this->direction = *dir;
  this->intensity = i;
}

float Spotlight::getIntensity()
{
  return this->intensity;
}

Vector Spotlight::getDirection()
{
  return this->direction;
}

Vertex Spotlight::getPosition()
{
  // explicit runtime_error( const std::string& "No position!" );
  throw "No position!";
  // throw std::runtime_error("No position");
}

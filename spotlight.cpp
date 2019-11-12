#include "spotlight.h"
#include <limits>

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

float Spotlight::getDistance(Vertex pointA){
  // No position to calc distance from
  return std::numeric_limits<float>::min();
  // return std::numeric_limits<float>::max();
}

#include "spotlight.h"
#include <limits>

Spotlight::Spotlight(Colour i, Vector *dir)
{
  dir->normalise();
  this->direction = *dir;
  this->intensity = i;
}

Colour Spotlight::getIntensity()
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
  return std::numeric_limits<float>::max();
  // return std::numeric_limits<float>::max();
}

Vector Spotlight::getRandEmittionDirection(){
  return this->direction;
}

Vertex Spotlight::getRandEmittionPosition(){
  // TODO: Complete fcn stub
}

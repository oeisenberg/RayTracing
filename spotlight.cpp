#include "spotlight.h"

Spotlight::Spotlight(float i, Vector *dir)
{
  dir->normalise();
  dir->negate();
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
  throw "No position!";
}

#include "pointlight.h"

Pointlight::Pointlight(float i, Vertex pos)
{
  dir->normalise();
  dir->negate();
  // this->direction = pos - hit.pos
  this->intensity = i;
  this->position = pos;
}

Pointlight::Pointlight(float i, Vertex pos, Vector dir, float n)
{
  dir->normalise();
  dir->negate();
  this->direction = dir;
  this->intensity = i;
  this->position = pos;
  this->falloff = n;
}

float Pointlight::getIntensity()
{
  return this->intensity;
}

Vector Pointlight::getDirection()
{
  return this->direction;
}

Vertex Pointlight::getPosition()
{
  return this->position;
}

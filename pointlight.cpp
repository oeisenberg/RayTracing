#include "pointlight.h"

Pointlight::Pointlight(float i, Vertex *pos)
{
  this->intensity = i;
  this->position = *pos;
}

float Pointlight::getIntensity()
{
  return this->intensity;
}

Vector Pointlight::getDirection()
{
    const char* what_arg = "Pointlight: No direction";
    throw std::runtime_error(what_arg);
}

Vector Pointlight::getDirection(Vertex hitPos)
{
  Vector newDir = this->position - hitPos;
  newDir.normalise();
  return newDir;
}

Vertex Pointlight::getPosition()
{
  return this->position;
}

float Pointlight::getDistance(Vertex pointA){
  Vector AB = this->position - pointA;
  return AB.length();
}

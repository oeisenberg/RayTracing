#include "pointlight.h"

Pointlight::Pointlight(float i, Vertex *pos)
{
  this->intensity = i;
  this->position = *pos;
}

// Pointlight::Pointlight(float i, Vertex pos, Vector dir, float n)
// {
//   dir->normalise();
//   dir->negate();
//   this->direction = dir;
//   this->intensity = i;
//   this->position = pos;
//   this->falloff = n;
// }

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

}

#include "pointlight.h"

Pointlight::Pointlight(Colour i, Vertex *pos)
{
  this->intensity = i;
  this->position = *pos;
}

Colour Pointlight::getIntensity()
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
  Vector newDir = hitPos - this->position;
  newDir.normalise();
  return newDir;
}

Vector Pointlight::getRandEmittionDirection(){
  int min = -1;
  int max = 1;
  float x, y, z, r;
  do {
    r = (float) rand() / (float) RAND_MAX; x = min + r * (max - min);
    r = (float) rand() / (float) RAND_MAX; y = min + r * (max - min);
    r = (float) rand() / (float) RAND_MAX; z = min + r * (max - min);
  } while (pow(x,2)+pow(y,2)+pow(z,2)>1);

  return Vector(x,y,z);
}

Vertex Pointlight::getRandEmittionPosition(){
  return getPosition();
}

Vertex Pointlight::getPosition()
{
  return this->position;
}

float Pointlight::getDistance(Vertex pointA){
  Vector AB = this->position - pointA;
  return AB.length();
}


#include "ambient.h"

Ambient::Ambient(float iA, float kA)
{
  I_ambient = iA;
  K_ambient = kA;
}

float Ambient::getCoeff()
{
  return I_ambient * K_ambient;
}

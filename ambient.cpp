
#include "ambient.h"

Ambient::Ambient(float iA)
{
  I_ambient = iA;
}

float Ambient::getCoeff(float K_ambient)
{
  return I_ambient * K_ambient;
}

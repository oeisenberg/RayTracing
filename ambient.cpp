
#include "ambient.h"

Ambient::Ambient(Colour *iA)
{
  I_ambient = iA;
}

Colour Ambient::getCoeff(float K_ambient)
{
  Colour &intensity = *I_ambient;
  return intensity * K_ambient;
}

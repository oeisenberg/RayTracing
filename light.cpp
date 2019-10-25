/***************************************************************************
*
* ohe - Oliver's Light Class
*/

#include "light.h"

Light::Light(float i)
{
  this->intensity = i;
}

Light::Light(float i, Vector *dir)
{
  dir->normalise();
  this->direction = *dir;
  this->intensity = i;
}

Light::Light(float i, Vertex p)
{
  this->intensity = i;
}

Light::Light(float i, Vertex p, Vector *dir)
{
  dir->normalise();
  this->direction = *dir;
  this->intensity = i;
}

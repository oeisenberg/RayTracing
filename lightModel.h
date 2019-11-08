/***************************************************************************
 *
 * ohe21 - Oliver's Light model class
 *
 */

// LIGHTMODEL is the base class for objects.
#ifndef _LIGHTMODEL_H_
#define _LIGHTMODEL_H_

#include "vector.h"

class LightModel {
public:

  virtual float getCoeff()
  {
  }

  virtual Vector getLightDir()
  {

  }

};

#endif

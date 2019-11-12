/***************************************************************************
 *
 * ohe21 - Oliver's Light model class
 *
 */

// LIGHTMODEL is the base class  for objects.
#ifndef _LIGHTMODEL_H_
#define _LIGHTMODEL_H_

#include <vector>
#include "vector.h"
#include "ray.h"
#include "hit.h"
#include "object.h"

class LightModel {
public:

  virtual float getCoeff()
  {
  }

  virtual Vector getLightDir()
  {

  }

  bool checkForShadow(Hit closest, std::vector<Object*> objs, Ray ray, float light_distance){
      Hit new_t = Hit();
      for (int i = 0; i < objs.size(); i++) {
        objs[i]->intersection(ray, new_t);

        if (new_t.flag)
        {
          // No need to test for all other objects once a shadow is confirmed
          return true;
        }
      }
      return false;
    };

};

#endif

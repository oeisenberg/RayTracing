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
#include "light.h"

class LightModel {
public:

  virtual float getCoeff()
  {
  }

  virtual Vector getLightDir()
  {

  }

  bool checkForShadow(Hit closest, std::vector<Object*> objs, Ray ray, Light* light){
      Hit new_t = Hit();
      float light_distance = light->getDistance(closest.position);
      for (int i = 0; i < objs.size(); i++) {
        objs[i]->intersection(ray, new_t);

        if (new_t.flag && ((light_distance-new_t.t) >= 0)) return true;
      }
      return false;
    };

};

#endif

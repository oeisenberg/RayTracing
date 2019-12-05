/***************************************************************************
 *
 * ohe21 - Oliver's Photon Class
 *
 */

#pragma once

#include "colour.h"
#include "hit.h"

class Photon {
public:
  Colour power;
  bool flag;
  float x;
  float y;
  float z;

	Photon()
	{
	}

	Photon(Colour i)
	{
    power = i;
    flag = false;
	}

  void calcReflectionPower(float probability){
    power = power / probability;
  }

  void storePosition(Hit h){
    x = h.position.x;
    y = h.position.z;
    z = h.position.y;
  }
};
/***************************************************************************
 *
 * ohe21 - Oliver's Photon Class
 *
 */

#pragma once

#include "colour.h"

class Photon : public Ray {
public:
  Colour power;

  Photon(){

  }

  Photon(Vertex p, Vector d, Colour i)
	{
		position = p;
		direction = d;
	  power = i;
	}

  void addColour(Colour other){
    power += other;
  }

  void calcReflectionPower(float probability, Colour coefficients){
    power = (power * coefficients) / probability;
  }
};

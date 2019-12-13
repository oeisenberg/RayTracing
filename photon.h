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
    position = Vertex();
    direction = Vector();
    power = Colour();
  }

  Photon(std::string t, Vertex p, Vector d, Colour i)
	{
    type = t;
		position = p;
		direction = d;
	  power = i;
	}

  void addColour(Colour other){
    power += other;
  }

  void calcPower(float probability, Colour coefficients){
    power = (power * coefficients) / probability;
  }
};

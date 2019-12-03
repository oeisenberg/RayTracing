/***************************************************************************
 *
 * ohe21 - Oliver's Photon Class
 *
 */

#pragma once

#include "colour.h"

class Photon {
public:
  Colour power;
  bool flag;

	Photon()
	{
	}

	Photon(Colour i)
	{
    power = i;
    flag = false;
	}
};

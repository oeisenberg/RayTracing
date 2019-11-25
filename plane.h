/***************************************************************************
 *
 * ohe21 - Oliver's Plane class
 *
 */

#pragma once

#include "object.h"

class Plane : public Object {
	Vertex position;
	Vector up;
public:
	Plane(Vertex position, Vector up, Material *m, float R, float G, float B);
	void intersection(Ray ray, Hit &hit);
};

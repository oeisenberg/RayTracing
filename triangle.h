/***************************************************************************
 *
 * ohe21 - Oliver's Triangle Classes Header file
 */

#pragma once

#include "object.h"

class Triangle : public Object {
Vertex a;
Vertex b;
Vertex c;

public:
	Triangle(Vertex a, Vertex b, Vertex c, float dC, float sC, float R, float G, float B);
	void intersection(Ray ray, Hit &hit);
};

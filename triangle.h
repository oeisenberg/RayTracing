/***************************************************************************
 *
 *
 */

#pragma once

#include "object.h"

class Triangle : public Object {
Vertex a;
Vertex b;
Vertex c;

public:
	Triangle(Vertex a, Vertex b, Vertex c);
	void intersection(Ray ray, Hit &hit);
};

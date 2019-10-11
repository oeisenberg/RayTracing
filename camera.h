#pragma once

#include "vertex.h"
#include "vector.h"

class Camera {
public:
	Vertex e;
	Vertex l;
	Vertex up;
	float d;

	Vector w;
	Vector u;
	Vector v;

	Camera(Vertex e, Vertex l, Vector up, float d);
};

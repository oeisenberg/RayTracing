#pragma once

#include "vertex.h"
#include "vector.h"
#include "ray.h"
#include "scene.h"

class Camera {
public:
	Vertex e;
	Vertex l;
	Vertex up;
	float d;

	Vector w;
	Vector u;
	Vector v;

	float FOV;

	Camera(Vertex e, Vertex l, Vector up, float d, float FOV);

	Ray getRay(Scene *sc, int x, int y);
};

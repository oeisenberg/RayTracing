#pragma once

#include "Sphere.h"
#include "object.h"

class Scene {
public:

	int width;
	int height;

	int nObjects;
	Object *Objects;

	Scene(int w, int h);
};

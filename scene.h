#pragma once

#include <memory>
#include <vector>
#include "Sphere.h"
#include "object.h"

class Scene {
public:

	int width;
	int height;

	int nObjects;
	std::vector<Object*> objects;

	Scene(int w, int h);
};

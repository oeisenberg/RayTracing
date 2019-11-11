#pragma once

#include <memory>
#include <vector>
#include "object.h"
#include "polymesh.h"

class Scene {
public:

	int width;
	int height;

	int nObjects;
	std::vector<Object*> objects;

	Scene(int w, int h);
	void addObject(Object *newObject);
	void addObject(PolyMesh *newObject);
};

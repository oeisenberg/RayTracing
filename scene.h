/***************************************************************************
 *
 * ohe21 - Oliver's Scene Class
 *
 */

#pragma once

#include <vector>
#include "sphere.h"
#include "object.h"
#include "polymesh.h"
#include "light.h"
#include "spotlight.h"
#include "pointlight.h"
#include "material.h"

class Scene {
public:

	int width;
	int height;
	int nObjects;
	std::vector<Object*> objects;
	std::vector<Light*> lights;

	Scene(int w, int h);
	void addObject(Object *newObject);
	void addObject(PolyMesh *newObject, Material *m);
	void addLight(Light *newLight);
	void addLight(Spotlight *newLight);
	void addLight(Pointlight *newLight);
};

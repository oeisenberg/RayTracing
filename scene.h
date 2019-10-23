#pragma once

#include <memory>
#include <vector>
#include "Sphere.h"
#include "object.h"
#include "polymesh.h"
#include "light.h"
#include "ambient.h"
#include "diffuse.h"

class Scene {
public:

	int width;
	int height;

	int nObjects;
	std::vector<Object*> objects;
	std::vector<Light*> lights;
	Ambient *AmbientLight;
	Diffuse *DiffuseLight;


	Scene(int w, int h);
	void addObject(Object *newObject);
	void addObject(PolyMesh *newObject, float dC, float Red, float Green, float Blue);
	void addLight(Ambient *newLight);
	void addLight(Diffuse *newLight);
};

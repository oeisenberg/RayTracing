#pragma once

#include <memory>
#include <vector>
#include "Sphere.h"
#include "object.h"
#include "polymesh.h"
#include "lightModel.h"
#include "ambient.h"
#include "diffuse.h"
#include "phong.h"

class Scene {
public:

	int width;
	int height;

	int nObjects;
	std::vector<Object*> objects;
	std::vector<Light*> lights;
	Ambient *AmbientLightModel;
	Diffuse *DiffuseLightModel;
	Phong *PhongLightModel;


	Scene(int w, int h);
	void addObject(Object *newObject);
	void addObject(PolyMesh *newObject, float dC, float Red, float Green, float Blue);
	void addLightModel(Ambient *newLightModel);
	void addLightModel(Diffuse *newLightModel);
	void addLightModel(Phong *newLightModel);
};

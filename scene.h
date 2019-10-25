#pragma once

#include <memory>
#include <vector>
#include "sphere.h"
#include "object.h"
#include "polymesh.h"
#include "lightModel.h"
#include "ambient.h"
#include "diffuse.h"
#include "specular.h"

class Scene {
public:

	int width;
	int height;

	int nObjects;
	std::vector<Object*> objects;
	std::vector<Light*> lights;
	Ambient *AmbientLightModel;
	Diffuse *DiffuseLightModel;
	Specular *SpecularLightModel;


	Scene(int w, int h);
	void addObject(Object *newObject);
	void addObject(PolyMesh *newObject, float aC, float dC, float dS, float Red, float Green, float Blue);
	void addLightModel(Ambient *newLightModel);
	void addLightModel(Diffuse *newLightModel);
	void addLightModel(Specular *newLightModel);
};

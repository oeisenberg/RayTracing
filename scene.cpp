/***************************************************************************
 *
 * ohe21 - Oliver's Scene Class
 *
 */

#include <vector>
#include <memory>
#include "scene.h"
#include "object.h"
#include "polymesh.h"
#include "triangle.h"
#include "vertex.h"
#include "lightModel.h"
#include "ambient.h"
#include "diffuse.h"
#include "specular.h"
// #include "spotlight.h"

Scene::Scene(int w, int h)
{
  this->width = w;
  this->height = h;

  Transform *transform = new Transform(1.0f, 0.0f, 0.0f, 0.0f,
                                       0.0f, 1.0f, 0.0f,-1.0f,
                                       0.0f, 0.0f, 1.0f, 7.0f,
                                       0.0f, 0.0f, 0.0f, 1.0f);

  // Create objs
  addObject(new Sphere(Vertex(-1, -1, 7), 1, 0.2, 0.5, 1, 1, 0, 0));
  addObject(new Sphere(Vertex(1, 2, 7), 2, 0.2, 0.2, 1, 0, 1, 0));
  addObject(new PolyMesh((char *)"teapot.ply", transform), 0.2, 0.5, 1, 0, 0, 1);

  // Add Lighting
  addLight(new Spotlight(0.5, new Vector(0, 0, 1)));
  // addLight(new Spotlight(0.3, new Vector(-1, -1, 0)));

  // Create light models
  addLightModel(new Ambient(0.2));
  addLightModel(new Diffuse());
  addLightModel(new Specular(20));
};

void Scene::addObject(Object *newObject)
{
  objects.push_back(newObject);
}

void Scene::addObject(PolyMesh *newObject, float aC, float dC, float sC, float Red, float Green, float Blue)
{
  for (int i = 0; i < newObject->triangle_count; i++)
  {
  		Vertex a = newObject->vertex[newObject->triangle[i][0]];
  		Vertex b = newObject->vertex[newObject->triangle[i][1]];
  		Vertex c = newObject->vertex[newObject->triangle[i][2]];

      addObject(new Triangle(a, b, c, aC, dC, sC, Red, Green, Blue));
  }
}

void Scene::addLightModel(Ambient *newLightModel)
{
  AmbientLightModel = newLightModel;
}

void Scene::addLightModel(Diffuse *newLightModel)
{
  DiffuseLightModel = newLightModel;
}

void Scene::addLightModel(Specular *newLightModel)
{
  SpecularLightModel = newLightModel;
}

void Scene::addLight(Spotlight *newLight){
  lights.push_back(newLight);
}

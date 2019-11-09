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
#include "spotlight.h"
#include "pointlight.h"
#include "material.h"

Scene::Scene(int w, int h)
{
  this->width = w;
  this->height = h;

  Transform *transform = new Transform(1.0f, 0.0f, 0.0f, 0.0f,
                                       0.0f, 0.0f, 1.0f, -2.0f,
                                       0.0f, 1.0f, 0.0f, 10.0f,
                                       0.0f, 0.0f, 0.0f, 1.0f);

  // Add Objects
  Material *shinyA = new Material(0.2, 0.5, 0.7);
  Material *shinyB = new Material(0.3, 0.4, 0.8);
  addObject(new Sphere(Vertex(0, 0, 100), 80, shinyA, 1, 0, 0));
  addObject(new Sphere(Vertex(3, 2, 9),    1, shinyA, 0, 1, 0));
  addObject(new Sphere(Vertex(-3, 2, 9),   1, shinyA, 0, 1, 0));
  addObject(new PolyMesh((char *)"teapotSmaller.ply", transform), shinyB, 0, 0, 1);

  // Add Lighting
  addLight(new Pointlight(0.8, new Vertex(0, 2, 9)));
  addLight(new Spotlight(0.7, new Vector(0.45, 0.1, 1)));
  addLight(new Spotlight(0.6, new Vector(0.55, 0.1, 1)));


  // Add Lighting Models
  addLightModel(new Ambient(0.4));
  addLightModel(new Diffuse());
  addLightModel(new Specular(20));
};

void Scene::addObject(Object *newObject)
{
  objects.push_back(newObject);
}

// Adds a Polymesh object to the scene as a series of triangles
void Scene::addObject(PolyMesh *newObject, Material *m, float Red, float Green, float Blue)
{
  for (int i = 0; i < newObject->triangle_count; i++)
  {
  		Vertex a = newObject->vertex[newObject->triangle[i][0]];
  		Vertex b = newObject->vertex[newObject->triangle[i][1]];
  		Vertex c = newObject->vertex[newObject->triangle[i][2]];

      addObject(new Triangle(a, b, c, m, Red, Green, Blue));
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

void Scene::addLight(Pointlight *newLight){
  lights.push_back(newLight);
}

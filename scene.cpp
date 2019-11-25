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
#include "plane.h"

Scene::Scene(int w, int h)
{
  this->width = w;
  this->height = h;

  Transform *transform = new Transform(1.0f, 0.0f, 0.0f, 0.0f,
                                       0.0f, 0.0f, 1.0f, -2.0f,
                                       0.0f, 1.0f, 0.0f, 10.0f,
                                       0.0f, 0.0f, 0.0f, 1.0f);

  // Init Objs Materials
  Material *shinyA = new Material(new Colour(0.578, 0.6, 1), 0.2, 0.3, 0.1);
  Material *planes = new Material(new Colour(0.3, 0.3, 0.3), 0.2, 0.3, 0.1);
  Material *tpot = new Material(new Colour(1, 0, 0), 0.2, 0.3, 0.1);
  Material *reflectiveA = new Material(new Colour(0, 1, 0), 0.3, 0.3, 0.6, true, false);
  Material *transparantA = new Material(new Colour(1, 0, 0), 0.3, 0.3, 0.6, false, true);

  // Add Objects
  addObject(new Sphere(Vertex(2, -1, 7),  1, reflectiveA));
  addObject(new Sphere(Vertex(-2, -1, 7), 1, reflectiveA));
  addObject(new PolyMesh((char *)"teapotSmaller.ply", transform), shinyA);
  addObject(new Plane(Vertex(0, -3, 0), Vector(0, 1, 0), planes));
  addObject(new Plane(Vertex(0, 0, 21), Vector(0, 0, 1), planes));

  // Add Lighting
  addLight(new Pointlight(0.6, new Vertex(0, 1, 7)));
  addLight(new Spotlight(0.6, new Vector(0.3, -1, 1)));
  addLight(new Spotlight(0.85, new Vector(-0.3, -1, 1)));

  // Add Lighting Models
  addLightModel(new Ambient(0.2));
  addLightModel(new Diffuse());
  addLightModel(new Specular(20));
};

void Scene::addObject(Object *newObject)
{
  objects.push_back(newObject);
}

// Adds a Polymesh object to the scene as a series of triangles
void Scene::addObject(PolyMesh *newObject, Material *m)
{
  for (int i = 0; i < newObject->triangle_count; i++)
  {
  		Vertex a = newObject->vertex[newObject->triangle[i][0]];
  		Vertex b = newObject->vertex[newObject->triangle[i][1]];
  		Vertex c = newObject->vertex[newObject->triangle[i][2]];

      addObject(new Triangle(a, b, c, m));
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

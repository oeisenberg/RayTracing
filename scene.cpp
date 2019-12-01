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
  Material *shinyA = new Material(Colour(1, 0, 0), Colour(0.2, 0.2, 0.2), Colour(0.4, 0.4, 0.4), Colour(0.4, 0.4, 0.4), 20);
  Material *planes = new Material(Colour(0.3, 0.3, 0.3), Colour(0.2, 0.2, 0.2), Colour(0.3, 0.3, 0.3), Colour(0.1, 0.1, 0.1), 20);
  // Material *tpot = new Material(Colour(1, 0, 0), 0.2, 0.3, 0.1);
  Material *reflectiveA = new Material(Colour(0, 1, 0), Colour(0.5, 0.5, 0.5), Colour(0.5, 0.5, 0.5), Colour(0.3, 0.3, 0.3), 20, true, false);
  Material *transparantA = new Material(Colour(0, 0, 1), Colour(0.5, 0.5, 0.5), Colour(0.5, 0.5, 0.5), Colour(0.3, 0.3, 0.3), 20, false, true);


  // Add Objects
  addObject(new Sphere(Vertex(2, -1, 7),  1, shinyA));
  addObject(new Sphere(Vertex(-2, -1, 7), 1, shinyA));
  addObject(new Sphere(Vertex(0, 0, 7), 0.8, reflectiveA));
  addObject(new Sphere(Vertex(0, 0, 4), 1.3, transparantA));
  // addObject(new PolyMesh((char *)"teapotSmaller.ply", transform), shinyA);
  addObject(new Plane(Vertex(0, -3, 0), Vector(0, 1, 0), planes));
  addObject(new Plane(Vertex(0, 0, 21), Vector(0, 0, 1), planes));

  // Add Lighting
  addLight(new Pointlight(Colour(0.5, 0.5, 0.5), new Vertex(0, 3, 7)));
  addLight(new Spotlight(Colour(0.6, 0.6, 0.6), new Vector(0.3, -1, 1)));
  addLight(new Spotlight(Colour(0.85, 0.85, 0.85), new Vector(-0.3, -1, 1)));

  // Add Lighting Models
  addLightModel(new Ambient(new Colour(0.2, 0.2, 0.2)));
  addLightModel(new Diffuse());
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

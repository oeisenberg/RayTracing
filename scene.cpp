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
#include "light.h"
#include "ambient.h"
#include "diffuse.h"

Scene::Scene(int w, int h)
{
  this->width = w;
  this->height = h;

  Transform *transform = new Transform(1.0f, 0.0f, 0.0f, 0.0f,
                                       0.0f, 1.0f, 0.0f,-1.0f,
                                       0.0f, 0.0f, 1.0f, 7.0f,
                                       0.0f, 0.0f, 0.0f, 1.0f);

  // Create objs
  addObject(new Sphere(Vertex(2, 2, 10), 3, 0.5, 1, 0, 0));
  addObject(new Sphere(Vertex(-1, -1, 7), 2, 0.2, 0, 1, 0));
  addObject(new PolyMesh((char *)"teapot.ply", transform), 0.5, 0, 0, 1);

  // Create lights
  addLight(new Ambient(0.2, 0.1));
  addLight(new Diffuse(0.6, Vector(0, -1, 1)));

};

void Scene::addObject(Object *newObject)
{
  objects.push_back(newObject);
}

void Scene::addObject(PolyMesh *newObject, float dC, float Red, float Green, float Blue)
{
  for (int i = 0; i < newObject->triangle_count; i++)
  {
  		Vertex a = newObject->vertex[newObject->triangle[i][0]];
  		Vertex b = newObject->vertex[newObject->triangle[i][1]];
  		Vertex c = newObject->vertex[newObject->triangle[i][2]];

      addObject(new Triangle(a, b, c, dC, Red, Green, Blue));
  }
}

void Scene::addLight(Ambient *newLight)
{
  AmbientLight = newLight;
}

void Scene::addLight(Diffuse *newLight)
{
  DiffuseLight = newLight;
}

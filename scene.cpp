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
  addObject(new Sphere(Vertex(1, 1, 4), 2));
  addObject(new Sphere(Vertex(0, 0, 8), 3));
  // addObject(new PolyMesh((char *)"teapot.ply", transform));

  // Create lights
  addLight(new Ambient(0.2, 0.1));
  addLight(new Diffuse(0.6, 0.1, Vector(0, 0, -1)));

};

void Scene::addObject(Object *newObject)
{
  objects.push_back(newObject);
}

void Scene::addObject(PolyMesh *newObject)
{
  for (int i = 0; i < newObject->triangle_count; i++)
  {
  		Vertex a = newObject->vertex[newObject->triangle[i][0]];
  		Vertex b = newObject->vertex[newObject->triangle[i][1]];
  		Vertex c = newObject->vertex[newObject->triangle[i][2]];

      objects.push_back(new Triangle(a, b, c));
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

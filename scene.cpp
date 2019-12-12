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
#include "spotlight.h"
#include "pointlight.h"
#include "material.h"
#include "plane.h"
#include "light.h"

Scene::Scene(int w, int h)
{
  this->width = w;
  this->height = h;

  Transform *transform = new Transform(1.0f, 0.0f, 0.0f, 0.0f,
                                       0.0f, 0.0f, 1.0f, -2.0f,
                                       0.0f, 1.0f, 0.0f, 10.0f,
                                       0.0f, 0.0f, 0.0f, 1.0f);

  // Init Objs Materials
  Material *shinyMetal = new Material(Colour(1.0),Colour(0.5), Colour(0.2), 20);
  Material *planesA = new Material(Colour(0.5),Colour(0.2), Colour(0.2), 20);
  Material *planesB = new Material(Colour(0.0, 0.0, 0.8), Colour(0.0, 0.0, 0.4), Colour(0.0, 0.0, 0.1), 20);
  Material *planesC = new Material(Colour(0.8, 0.0, 0.0), Colour(0.4, 0.0, 0.0), Colour(0.1, 0.0, 0.0), 20);
  Material *planesD = new Material(Colour(0.1), Colour(0.01), Colour(0.01), 20);
  Material *planesE = new Material(Colour(0.7), Colour(0.5), Colour(0.02), 20, 0.001);
  // Material *teapot = new Material(Colour(1, 0, 0), 0.2, 0.3, 0.1);
  Material *reflectiveA = new Material(Colour(1), Colour(0.6), Colour(0.2), 20, Colour(0.5));
  Material *transparantA = new Material(Colour(1), Colour(0.5), Colour(0.4), 20, Colour(0.1), Colour(0.8), 1.51);


  // Add Objects
  addObject(new Sphere(Vertex(-3, 0, 12), 1, shinyMetal));
  addObject(new Sphere(Vertex(-1.5, -2, 8), 0.8, reflectiveA));
  addObject(new Sphere(Vertex(1.5, -2, 8), 0.8, transparantA));
  // addObject(new PolyMesh((char *)"teapotSmaller.ply", transform), shinyA);
  addObject(new Plane(Vertex(0, -3, 0), Vector(0, 1, 0), planesA));
  addObject(new Plane(Vertex(0, 0, 15), Vector(0, 0, -1), planesE));
  addObject(new Plane(Vertex(4, 0, 0), Vector(-1, 0, 0), planesB));
  addObject(new Plane(Vertex(-4, 0, 0), Vector(1, 0, 0), planesC));
  addObject(new Plane(Vertex(0, 5.5, 0), Vector(0, -1, 0), planesD));
  addObject(new Plane(Vertex(0, 0, -0.5), Vector(0, 0, 1), planesD));

  // Add Lighting
  addLight(new Pointlight(Colour(1, 1, 1), new Vertex(0, 5, 10)));
  // addLight(new Pointlight(Colour(1, 1, 1), new Vertex(0, 5, 11.9)));
  // addLight(new Pointlight(Colour(1, 1, 1), new Vertex(0, 5, 11.8)));
  // addLight(new Spotlight(Colour(1.0, 1.0, 1.0), new Vector(0, 0, 1)));
  // addLight(new Spotlight(Colour(0.85, 0.85, 0.85), new Vector(-0.3, -1, 2)));
};

void Scene::addObject(Object *newObject)
{
  nObjects++;
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
  nObjects -= newObject->triangle_count;
}

void Scene::addLight(Spotlight *newLight){
  lights.push_back(newLight);
}

void Scene::addLight(Pointlight *newLight){
  lights.push_back(newLight);
}

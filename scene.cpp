/***************************************************************************
 *
 * ohe21 - Oliver's Scene Class
 * Holds all infomation about contents of the scene
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

// Transform to be applied to the polymesh
Transform *transform = new Transform(1.0f, 0.0f, 0.0f, 0.0f,
                                       0.0f, 0.0f, 1.0f, -2.0f,
                                       0.0f, 1.0f, 0.0f, 10.0f,
                                       0.0f, 0.0f, 0.0f, 1.0f);

  // Init Objs Materials
  Material *shinyMetal = new Material(Colour(1),Colour(0.5), Colour(0.4), 20);
  Material *reflectiveBall = new Material(Colour(1),Colour(0),Colour(1),20,1);
  
  Material *floor = new Material(Colour(1), Colour(0.3), Colour(0.4), 20);
  // Material *reflectiveA = new Material(Colour(0), Colour(0.3), Colour(0.4), 2, Colour(0.8));
  Material *transparantA = new Material(Colour(0), Colour(0.1,0.1,0.1), Colour(0.1,0.1,0.1), 20, Colour(0.6), Colour(1), 1.33);

  // addObject(new PolyMesh((char *)"teapotSmaller.ply", transform), transparantA);
  addObject(new Plane(Vertex(0, -3, 0), Vector(0, 1, 0), floor));

  addObject(new Sphere(Vertex(0,3,7), 2, transparantA));
  addObject(new Sphere(Vertex(0,3,7), 0.1, shinyMetal));
  addObject(new Sphere(Vertex(-3,0,7), 0.5, shinyMetal));
  addObject(new Sphere(Vertex(3,0,7), 0.5, shinyMetal));
  addLight(new Pointlight(Colour(1), new Vertex(0, 5, 7)));
  addLight(new Spotlight(Colour(0.1), new Vector(0,-0.6,1)));
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

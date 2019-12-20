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
  Material *shinyMetal = new Material(Colour(1),   Colour(0.4),           Colour(0.3), 20);
  
  Material *floor = new Material(Colour(1),        Colour(0.3),           Colour(0.4), 20);
  Material *rearWall = new Material(Colour(1),     Colour(0.6, 0.2, 0.5), Colour(0.2), 20);
  Material *reflective = new Material(Colour(1),    Colour(0.3),          Colour(0.5), 1, Colour(0.5));
  Material *W = new Material(Colour(1),            Colour(0, 0.1, 0.5),   Colour(0, 0, 0.1), 1);
  Material *transparantG = new Material(Colour(1), Colour(0.0,0.1,0.01),  Colour(0.1,0.1,0.01), 1, Colour(0.01), Colour(0.5), 1.51);
  Material *transparantW = new Material(Colour(1),  Colour(0.1),  Colour(0.1), 1, Colour(0.01), Colour(0.5), 1.51);
  Material *sphereA = new Material(Colour(1),      Colour(0.2,0.01,0.4),  Colour(0.1), 1);
  Material *sphereB = new Material(Colour(1),      Colour(0.4,0.0,0.0),   Colour(0.1), 1);
  Material *sphereC = new Material(Colour(1),      Colour(0.7),     Colour(0.2), 4);

  addObject(new Plane(Vertex(0, -2, 0), Vector(0, 1, 0), floor));
  addObject(new Plane(Vertex(0, 0, 10.5), Vector(0, 0, -1), rearWall));

  addObject(new Sphere(Vertex(-1.7,-1.5,6.5), 0.5, transparantG));
  addObject(new Sphere(Vertex(-0.3,-1.5,6.5), 0.5, sphereA));
  addObject(new Sphere(Vertex(-1,-0.9,6.5), 0.5, transparantW));
  addObject(new PolyMesh((char *)"teapotSmaller.ply", transform), shinyMetal);

  addObject(new Sphere(Vertex(2.3,-1.75,9.5), 0.25, W));
  addObject(new Sphere(Vertex(0.5,-1.7,7.5), 0.3, sphereB));
  addObject(new Sphere(Vertex(1,1.2,9.8), 0.7, reflective));

  addLight(new Pointlight(Colour(0.4), new Vertex(0, 0, 10)));
  addLight(new Spotlight(Colour(0.3), new Vector(0.2, -1, 0.8)));
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

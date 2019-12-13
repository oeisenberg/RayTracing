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
  Material *shinyMetal = new Material(Colour(1),Colour(1), Colour(0.5), 20);
  Material *shinyMetalA = new Material(Colour(0.1),Colour(0.2, 0, 0), Colour(0.4, 0, 0), 20);
  Material *shinyMetalB = new Material(Colour(0.1),Colour(0.2, 0, 0.2), Colour(0.4, 0, 0.4), 20);
  
  Material *floor = new Material(Colour(0.5),Colour(0.7), Colour(0.2), 20);
  Material *greenWall = new Material(Colour(0.0, 0.3, 0.0), Colour(0.0, 0.3, 0.0), Colour(0.0, 0.1, 0.0), 20);
  Material *redWall = new Material(Colour(0.3, 0.0, 0.0), Colour(0.3, 0.0, 0.0), Colour(0.1, 0.0, 0.0), 20);
  Material *oppositeWalls = new Material(Colour(0.5), Colour(1), Colour(0.05), 10);
  Material *planesF = new Material(Colour(0.01), Colour(0.01), Colour(0.01), 1);
  Material *rough = new Material(Colour(0.1), Colour(0.3), Colour(0.3), 10, Colour(0), Colour(0), 1, 0.3);
  // Material *teapot = new Material(Colour(1, 0, 0), 0.2, 0.3, 0.1);
  Material *reflectiveA = new Material(Colour(0.1), Colour(0.5), Colour(0.3), 2, Colour(0.8));
  Material *transparantA = new Material(Colour(0.1), Colour(0.5), Colour(0.3), 20, Colour(0.1), Colour(0.8), 1.51);


 
  // Simple pointlights demo:
    // // Add Objects
    //   addObject(new Sphere(Vertex(-2, 0, 9), 1, shinyMetalA));
    //   addObject(new Sphere(Vertex(2, 0, 9), 1, shinyMetalB));
    // // Add Lighting
    //   addLight(new Pointlight(Colour(1, 1, 1), new Vertex(0, 1, 9)));

  // // // Cornel Box:
      addObject(new Sphere(Vertex(-3, 0, 12), 1, shinyMetal));
      addObject(new Sphere(Vertex(-1.5, -2, 8), 0.8, reflectiveA));
      addObject(new Sphere(Vertex(1.5, -2, 8), 0.8, transparantA));
  // //     // addObject(new PolyMesh((char *)"teapotSmaller.ply", transform), shinyA);
      addObject(new Plane(Vertex(0, -3, 0), Vector(0, 1, 0), floor));
      addObject(new Plane(Vertex(0, 0, 15), Vector(0, 0, -1), oppositeWalls));
      addObject(new Plane(Vertex(4, 0, 0), Vector(-1, 0, 0), greenWall));
      addObject(new Plane(Vertex(-4, 0, 0), Vector(1, 0, 0), redWall));
      addObject(new Plane(Vertex(0, 5.5, 0), Vector(0, 1, 0), planesF));
      addObject(new Plane(Vertex(0, 0, -0.5), Vector(0, 0, 1), oppositeWalls));

      addLight(new Pointlight(Colour(1, 1, 1), new Vertex(0, 4.7, 11)));

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

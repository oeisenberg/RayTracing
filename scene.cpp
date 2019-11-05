#include <memory.h>
#include "scene.h"
#include "object.h"

Scene::Scene(int w, int h)
{
  this->width = w;
  this->height = h;

  // Create objs
  this->nObjects = 2;
  Sphere *sphereA = new Sphere(Vertex(7,7,7), 10); //std::shared_ptr<...>
  Sphere *sphereB = new Sphere(Vertex(8,8,8), 15);
  Object *objs = new Object[this->nObjects];
  objs[0] = *sphereA;
  objs[1] = *sphereB;
  this->Objects = objs;

  // std::cout << sphereA->radius;
  // std::cout << objs[0]->radius;
  // std::cout << dynamic_cast<Sphere*>(this->Objects)->radius;
};

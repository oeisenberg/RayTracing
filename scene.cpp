#include <memory>
#include "scene.h"
#include "object.h"
#include "polymesh.h"
#include "triangle.h"
#include "vertex.h"
#include <vector>

Scene::Scene(int w, int h)
{
  this->width = w;
  this->height = h;

  Transform *transform = new Transform(1.0f, 0.0f, 0.0f, 0.0f,0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 7.0f,0.0f,0.0f,0.0f,1.0f);

  // Create objs
  // objects.push_back(new Sphere(Vertex(0,0,7), 2));
  // objects.push_back(new Sphere(Vertex(6,6,5), 5));
  PolyMesh *pm = new PolyMesh((char *)"teapot.ply", transform);
  for (int i = 0; i < pm->triangle_count; i++)
  {
  		Vertex a = pm->vertex[pm->triangle[i][0]];
  		Vertex b = pm->vertex[pm->triangle[i][1]];
  		Vertex c = pm->vertex[pm->triangle[i][2]];

      objects.push_back(new Triangle(a, b, c));
  }

  this->nObjects = objects.size();
};

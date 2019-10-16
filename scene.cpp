#include <memory>
#include "scene.h"
#include "object.h"
#include "polymesh.h"
#include "triangle.h"

Scene::Scene(int w, int h)
{
  this->width = w;
  this->height = h;

  Transform *transform = new Transform(1.0f, 0.0f, 0.0f, 0.0f,0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 7.0f,0.0f,0.0f,0.0f,1.0f);

  // Create objs
  // objects.push_back(new Sphere(Vertex(4,4,5), 4));
  // objects.push_back(new Sphere(Vertex(6,6,5), 5));
  PolyMesh *pm = new PolyMesh((char *)"teapot.ply", transform);
  // for (int i = 0; i < pm->triangle_count; i++)
  // {
  //   objects.push_back(new Triangle(pm->triangles[i][0], pm->triangles[i][1], pm->triangles[i][2]));
  //   // Triangle *t = new Triangle(pm->triangles[i][0], pm->triangles[i][1], pm->triangles[i][2]);
  // }

  this->nObjects = objects.size();
};

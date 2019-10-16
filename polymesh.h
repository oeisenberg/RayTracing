/***************************************************************************
 *
 * krt - Kens Raytracer - Coursework Edition. (C) Copyright 1997-2019.
 *
 * Do what you like with this code as long as you retain this comment.
 */

#pragma once

#include "vertex.h"
#include "transform.h"
#include <vector>
#include <string>

typedef int TriangleIndex[3];
typedef Vertex wholeTriangle;

class PolyMesh {
public:
	int vertex_count;
	int triangle_count;
        Vertex *vertex;
	TriangleIndex *triangle;
	std::vector<wholeTriangle*> triangles;

	void do_construct(char *file, Transform *transform);
	std::vector<std::string> do_split(std::string inputString);

	PolyMesh(char *file);
	PolyMesh(char *file, Transform *transform);
};

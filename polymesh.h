/***************************************************************************
 *
 *
 */

#pragma once

#include "vertex.h"
#include "transform.h"
#include <vector>
#include <string>

typedef int TriangleIndex[3];

class PolyMesh {
public:
	int vertex_count;
	int triangle_count;
        Vertex *vertex;
	TriangleIndex *triangle;

	void do_construct(char *file, Transform *transform);
	std::vector<std::string> do_split(std::string inputString);

	PolyMesh(char *file);
	PolyMesh(char *file, Transform *transform);
};

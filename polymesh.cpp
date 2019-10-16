/***************************************************************************
 *
 * krt - Kens Raytracer - Coursework Edition. (C) Copyright 1997-2019.
 *
 * Do what you like with this code as long as you retain this comment.
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <typeinfo>

#include "math.h"
#include "polymesh.h"


PolyMesh::PolyMesh(char *file)
{
	Transform *transform = new Transform();

	this->do_construct(file, transform);
}

PolyMesh::PolyMesh(char *file, Transform *transform)
{
	this->do_construct(file, transform);
}

void PolyMesh::do_construct(char *file, Transform *transform)
{
	std::ifstream newFile(file);
	std::string line;

	getline(newFile, line); //Remove header line

	getline(newFile, line);
	std::string newline = line.c_str();

	std::vector<std::string> tokens = PolyMesh::do_split(newline);
	std::string nVerticies = tokens.back();
	PolyMesh::vertex_count = stoi(nVerticies);

	getline(newFile, line);
	newline = line.c_str();

	tokens = PolyMesh::do_split(newline);
	std::string nFaces = tokens.back();
	PolyMesh::triangle_count = stoi(nFaces);

	Vertex *vertex = new Vertex[PolyMesh::vertex_count];
	TriangleIndex *triangle = new TriangleIndex[PolyMesh::triangle_count];

	for (int lineNo = 3; getline(newFile, line) && lineNo <= PolyMesh::vertex_count + PolyMesh::triangle_count + 3; lineNo++)
	{
		std::string newline = line.c_str();

		std::vector<std::string> tokens = PolyMesh::do_split(newline);

		if (tokens.size() == 3) // Vertex
		{
			float x = atof(tokens.at(0).c_str());
			float y = atof(tokens.at(1).c_str());
			float z = atof(tokens.at(2).c_str());

			vertex[lineNo - 3] = Vertex(x, y, z);

			transform->apply(vertex[lineNo - 3]);
		}
		else if (tokens.size() == 4) { // Face

			for (int iToken = 1; iToken <= 3; iToken++) {
				triangle[lineNo - PolyMesh::vertex_count - 3][iToken - 1] = atoi(tokens.at(iToken).c_str()) - 1;
			}
		}
		else if (tokens.size() != 1) {
			std::cerr << "Error, " << tokens.size() << ": ";
		}
	}

	PolyMesh::vertex = vertex;
	PolyMesh::triangle = triangle;
	std::vector<wholeTriangle*> wholeTrianglesList;
	wholeTriangle *newTriangle = new wholeTriangle[0];

	for (int i = 0; i< triangle_count; i ++)
	{
		newTriangle[0] = vertex[triangle[i][0]];
		newTriangle[1] = vertex[triangle[i][1]];
		newTriangle[2] = vertex[triangle[i][2]];

		// wholeTrianglesList.push_back(newTriangle); //SEGMENTAION FAULT
	}

	// PolyMesh::triangles = wholeTrianglesList;
	newFile.close();
}

// Function to split strings into components for evaluation
std::vector<std::string> PolyMesh::do_split(std::string inputString)
{
	std::string segments;					 // Have a buffer string
	std::stringstream ss(inputString);       // Insert the string into a stream
	std::vector<std::string> output;

	while (ss >> segments)
	{
		output.push_back(segments);
	}

	return output;
}

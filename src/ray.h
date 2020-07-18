/***************************************************************************
 *
 * krt - Kens Raytracer - Coursework Edition. (C) Copyright 1997-2019.
 *
 * Do what you like with this code as long as you retain this comment.
 */

// Ray is a class to store and maniplulate 3D rays.

#pragma once

#include "vertex.h"
#include "vector.h"

class Ray {
public:
	Vertex position;
	Vector direction;
	std::string type;

	Ray()
	{
	}

	Ray(Vertex p, Vector d)
	{
		type = " ";
		position = p;
		direction = d;
	}

	Ray(std::string t, Vertex p, Vector d)
	{
		type = t;
		position = p;
		direction = d;
	}
};

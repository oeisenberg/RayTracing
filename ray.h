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
#include "photon.h"

class Ray {
public:
	Vertex position;
	Vector direction;
	Photon photon;

	Ray()
	{
	}

	Ray(Vertex p, Vector d)
	{
		position = p;
		direction = d;
	}

	Ray(Vertex p, Vector d, Photon ph)
	{
		position = p;
		direction = d;
		photon = ph;
	}
};

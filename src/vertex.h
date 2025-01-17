/***************************************************************************
 *
 * krt - Kens Raytracer - Coursework Edition. (C) Copyright 1997-2019.
 *
 * Do what you like with this code as long as you retain this comment.
 */

#pragma once
#include "vector.h"

class Vertex {
public:
	float x;
	float y;
	float z;
	float w;

	Vertex()
	{
		x = 0.0;
		y = 0.0;
		z = 0.0;
		w = 1.0f;
	}

	Vertex(float px, float py, float pz, float pw)
	{
		x = px;
		y = py;
		z = pz;
		w = pw;
	}

	Vertex(float px, float py, float pz)
	{
		x = px;
		y = py;
		z = pz;
		w = 1.0f;
	}

	Vector operator + (const Vertex& other)
	{
		return Vector(x+other.x, y+other.y, z+other.z);
	}

	Vertex operator + (const Vector& other)
	{
		return Vertex(this->x+other.x, this->y+other.y, this->z+other.z);
	}

	Vector operator - (const Vertex& other)
	{
		return Vector(this->x-other.x, this->y-other.y, this->z-other.z);
	}

	Vertex operator - (const Vector& other)
	{
		return Vertex(this->x-other.x, this->y-other.y, this->z-other.z);
	}

	Vector convertToVector()
	{
		return Vector(x, y, z);
	}

	Vertex operator + (const float other)
	{
		return Vertex(this->x+other, this->y+other, this->z+other);
	}

	Vertex operator - (const float other)
	{
		return Vertex(this->x-other, this->y-other, this->z-other);
	}
};

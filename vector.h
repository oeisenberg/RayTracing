/***************************************************************************
 *
 * krt - Kens Raytracer - Coursework Edition. (C) Copyright 1997-2019.
 *
 * Do what you like with this code as long as you retain this comment.
 */

#pragma once

#include <math.h>
#include <iostream>

class Vector {
public:
	float x;
	float y;
	float z;

	Vector(float px, float py, float pz)
	{
		x = px;
		y = py;
		z = pz;
	}

	Vector()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}

	void normalise()
	{
		float len = length();
		x = x / len;
		y = y / len;
		z = z / len;
	}

	float length()
	{
		return sqrt((double)(x*x + y*y + z*z));
	}

	float dot(Vector &other)
	{
		return x*other.x + y*other.y + z*other.z;
	}

	void reflection(Vector initial, Vector &reflect)
	{
		float d;

		d = dot(initial);
		d = d * 2.0f;

		reflect.x = initial.x - d * x;
		reflect.y = initial.y - d * y;
		reflect.z = initial.z - d * z;
	}

	void negate()
	{
		x = -x;
		y = -y;
		z = -z;
	}

	void cross(Vector &other, Vector &result)
	{
	  result.x = y*other.z - z*other.y;
	  result.y = z*other.x - x*other.z;
	  result.z = x*other.y - y*other.x;
	}

	Vector multiply(int scalar)
	{
		float new_x = x * scalar;
		float new_y = y * scalar;
		float new_z = z * scalar;
		return Vector(new_x, new_y, new_z);
	}

	Vector operator + (const Vector& other)
	{
		return Vector(x+other.x, y+other.y, z+other.z);
	}

	Vector operator - (const Vector& other)
	{
		return Vector(x-other.x, y-other.y, z-other.z);
	}
};

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
		float len = (float)sqrt((double)(x*x + y*y + z*z));
		x = x / len;
		y = y / len;
		z = z / len;
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

	Vector multiply(Vector &other)
	{
		x = x * other.x;
		y = y * other.y;
		z = z * other.z;
	}

	Vector divide(Vector other)
	{
		float new_x = x / other.x;
		float new_y = y / other.y;
		float new_z = z / other.z;
		return Vector(new_x, new_y, new_z);
	}

	Vector absolute()
	{
		//std::cout << "=: ("<< x << ", " << y << ", " << z << ")" << std::endl;
		x = abs(x);
		y = abs(y);
		z = abs(z);
		//std::cout << "=: ("<< x << ", " << y << ", " << z << ")" << std::endl;
	}
};

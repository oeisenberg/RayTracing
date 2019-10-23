/***************************************************************************
 *
 * krt - Kens Raytracer - Coursework Edition. (C) Copyright 1997-2019.
 *
 * Do what you like with this code as long as you retain this comment.
 */

// Object is the base class for objects.
#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "ray.h"
#include "hit.h"

class Object {
public:
	// Colour Values
	float R;
	float G;
	float B;

	// Diffuse Coeff
	float dCoeff;

	// Phong coeff
	// float pCoeff;

	Object *next;

	Object()
	{
		next = (Object *)0;
	}

	virtual void intersection(Ray ray, Hit &hit)
	{

	}
};

#endif

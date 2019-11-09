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
#include "material.h"
#include "hit.h"

class Object {
public:
	// Colour Values
	float R;
	float G;
	float B;

	// Ambeint Coeff
	float aCoeff;
	// Diffuse Coeff
	float dCoeff;
	// Specular Coeff
	float sCoeff;

	Material *objMaterial;

	// Distribution
	int n; //TODO: Fully implement so objects have their own n

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

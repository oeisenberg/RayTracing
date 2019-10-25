/***************************************************************************
 *
 * krt - Kens Raytracer - Coursework Edition. (C) Copyright 1997-2019.
 *
 * Do what you like with this code as long as you retain this comment.
 */

#pragma once

#include "vertex.h"
#include "object.h"
#include "scene.h"

class Teapot : public Object {
	Vertex center;
public:
	Teapot(Scene *s, Vertex c);
	void intersection(Ray ray, Hit &hit);
};

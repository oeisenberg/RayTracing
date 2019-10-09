/***************************************************************************
 *
 * krt - Kens Raytracer - Coursework Edition. (C) Copyright 1997-2019.
 *
 * Do what you like with this code as long as you retain this comment.
 */

/* This is the code you will need to replace for Lab 1.
 *
 * It contains two simple implementations that loop over the longest axis adding the gradient to the position on the other axis at each step.
 * The objective is for you to remove the use of floating point variables and work entirely with integers.
 * You should use Bresenhams Line Algorithm to achieve this.
 */

#include <iostream>
#include "linedrawer.h"

int draw_x_line_int(FrameBuffer *fb, int sx, int sy, int ex, int ey)
{
	int x = sx;        int y = sy;
	int dx = ex - sx;  int dy = ey - sy;
	int xdir = 1;      int ydir = 1;

	if (sx > ex) // LHS
	{
		xdir = -1;
		dx = dx * xdir;
	}

	if (sy > ey) // DWN
	{
		ydir = -1;
		dy = dy * ydir;
	}

	dy = 2 * dy;
	int p = dy - dx;

	// otherwise just plots one side of the x-axis
	while (x != ex){
		fb->plotPixel(x, y, 1.0f, 1.0f, 1.0f);
		x += xdir;

		if (p < 0)
		{
			p = p + dy;
		} else {
			p = p + dy - 2 * dx;
			y += ydir;
		}
	}

}

int draw_y_line_int(FrameBuffer *fb, int ex, int ey, int sx, int sy)
{
	int x = sx;        int y = sy;
	int dx = ex - sx;  int dy = ey - sy;
	int xdir = 1;      int ydir = 1;

	if (sx > ex) // LHS
	{
		xdir = -1;
		dx = dx * xdir;
	}

	if (sy > ey) // DWN
	{
		ydir = -1;
		dy = dy * ydir;
	}

	dx = 2 * dx;
	int p = dx - dy;

	// otherwise just plots one side of the y-axis
	while (y != ey){
		fb->plotPixel(x, y, 1.0f, 1.0f, 1.0f);
		y += ydir;

		if (p < 0)
		{
			p = p + dx;
		} else {
			p = p + dx - 2 * dy;
			x += xdir;
		}
	}
}

int draw_line(FrameBuffer *fb, int sx, int sy, int ex, int ey)
{
	if ((sx == ex) && (sy==ey))
	{
		return fb->plotPixel(sx, sy, 1.0f, 1.0f, 1.0f);
	} else if (((ex-sx)* (ex-sx)) >= ((ey-sy)* (ey-sy))) {
		return draw_x_line_int(fb, sx, sy, ex, ey);
	} else {
		return draw_y_line_int(fb, sx, sy, ex, ey);
	}
}

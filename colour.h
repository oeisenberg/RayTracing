#pragma once

class Colour {
public:
  float R;
  float G;
  float B;

  Colour()
	{
	}

	Colour(float r, float b, float g)
	{
		R = r;
    G = g;
    B = b;
	}

  void clear()
  {
    R = 0;
    G = 0;
    B = 0;
  }

};

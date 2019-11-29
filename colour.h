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

  Colour operator + (const Colour& other){
    return Colour(R+other.R, G+other.G, B+other.B);
  }

  Colour operator * (const Colour& other){
    return Colour(R*other.R, G*other.G, B*other.B);
  }

};

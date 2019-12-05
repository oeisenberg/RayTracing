#pragma once

#include<algorithm>

class Colour {
public:
  float R;
  float G;
  float B;

  Colour()
	{
    R = 0;
    G = 0;
    B = 0;
	}

	Colour(float r, float g, float b)
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

  void operator += (const Colour& other){
    R = R+other.R;
    G = G+other.G;
    B = B+other.B;
  }

  Colour operator * (const Colour& other){
    return Colour(R*other.R, G*other.G, B*other.B);
  }

  Colour operator * (const float& other){
    return Colour(R*other, G*other, B*other);
  }

  Colour operator / (const int& other){
    return Colour(R/(float)other, G/(float)other, B/(float)other);
  }

  Colour operator / (const float& other){
    return Colour(R/other, G/other, B/other);
  }

  float getStrength(){
    return std::max(std::max(R, G), B);
  };

};

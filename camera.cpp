#include <iostream>
#include "camera.h"
#include "vector.h"
#include "vertex.h"
#include <math.h>

Camera::Camera(Vertex Eye, Vertex Look, Vector Up, float D){
  Vector EyeMinusLook = Vector(Eye.x - Look.x, Eye.y - Look.y, Eye.z - Look.z);

  std::cout << "Eye: ("<< Eye.x << ", " << Eye.y << ", " << Eye.z << ")" << std::endl;
  std::cout << "Look: ("<< Look.x << ", " << Look.y << ", " << Look.z << ")" << std::endl;
  std::cout << "-"<< std::endl;
  //EyeMinusLook.absolute();
  std::cout << "=: ("<< EyeMinusLook.x << ", " << EyeMinusLook.y << ", " << EyeMinusLook.z << ")" << std::endl;
	//this->w = EyeMinusLook.divide(EyeMinusLook.absolute());
  std::cout << EyeMinusLook.divide(EyeMinusLook.absolute()).x;
  //this->u = Up.multiply(w).divide(Up.multiply(this->w).absolute());
  //this->v = (this->w).multiply(this->u);
}

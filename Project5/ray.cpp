#include "ray.h" 

Vector3f point;
Vector3f direction;

ray::ray(Vector3f point, Vector3f direction){
	this->point = point;
	this->direction = direction;
	this->direction.normalize();
}
Vector3f ray::getPoint(){
	return this->point;
}
Vector3f ray::getDirection(){
	return this->direction;
}

void ray::setMinusDiscriminent(bool setMinus) {
	this->minusDiscriminent = setMinus;
}
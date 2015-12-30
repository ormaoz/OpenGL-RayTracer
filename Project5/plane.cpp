using namespace std;
#include <stdio.h>
#include "light.h"
#include "shape.h"
#include "glut.h"
#include "ray.h"
#include "plane.h"
#include "fileParse.h"

/*
Constructor
*/
plane::plane(Vector3f Normal, Vector3f Point, Vector3f Ka, Vector3f Kd, Vector3f Ks, float Shininess) : shape(Ka, Kd, Ks, Shininess){
	this->shininess = Shininess;
	this->ka = Ka;
	this->kd = Kd;
	this->ks = Ks;
	this->normal = Normal;
	this->point = Point;
}
	
plane::~plane(void){

}
	
/*
Finds the intersection between a ray and the plane using the formula from PS3 Slide 32.
*/
float plane::intersection(ray* r) {
	Vector3f intersect;
	Vector3f rayPoint = r->getPoint();
	Vector3f rayDirection = r->getDirection();
	normal.normalize();
	
	// Check the normal isn't ortohgonal to the ray's direction.
	if (Vector3f::dotProduct(this->normal, rayDirection) != 0) {
		intersect = this->point - rayPoint;
		intersect = intersect.operator/(Vector3f::dotProduct(this->normal, rayDirection));
		float t = Vector3f::dotProduct(normal, intersect);
		if (t > 0) {
			return t;
		}
	}
	// If it does there is no intersection.
	else {
		return FLT_MAX;
	}
}

/*
Return the normal in a certain point. In a plane all normals are the same.
*/
Vector3f plane::getNormal(Vector3f p) {
	return normal;
}

/* 
Return the point which defined the plain
*/
Vector3f plane::getPoint(){
	return point;
}
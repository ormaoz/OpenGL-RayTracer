#pragma once
#include <stdio.h>
#include <math.h>
#include "light.h"
#include "glut.h"
#include "ray.h"
#include "sphere.h"
#include "fileParse.h"

using namespace std;

#pragma once

/*
Constructor
*/
sphere::sphere(Vector3f Center, float Radius, Vector3f Ka, Vector3f Kd, Vector3f Ks, float Shininess) : shape(Ka, Kd, Ks, Shininess){
		this->ka = Ka;
		this->kd = Kd;
		this->ks = Ks;
		this->radius = Radius;
		this->center = Center;
		this->shininess = Shininess;
	}


sphere::~sphere(void) {
}

/*
This method finds the intersection between a ray and the sphere.
If there is no interesection returns max float.
*/
float sphere::intersection(ray* r) {
	Vector3f l;
	Vector3f v;

	l = Vector3f(r->getPoint() - this->center); // Vector from eye to center of the sphere
	v = r->getDirection();
	float b = 2.0 * v.dotProduct(l, v);
	float c = l.getSquaredLength() - (this->radius * this->radius);

	// There is an intersection
	if (b*b - 4 * c >= 0) { // Checks whether the light ray from eye hit the sphere 

		// Two intersection points
		float t1 = (-b + sqrt(b*b - 4 * c)) / 2.0;
		float t2 = (-b - sqrt(b*b - 4 * c)) / 2.0;

		// Returns the closer point between the two intersection points
		if (t1 > t2) {
			return t2;
		}
		else {
			r->setMinusDiscriminent(true);
			return t1;
		}
	}
	return FLT_MAX;
}

/*
Returns the normal in a given point.
*/
Vector3f sphere::getNormal(Vector3f p) {
			
	Vector3f norm = (p - center);
	norm.normalize();
	return norm;
}

/*
Returns the sphere's radius
*/
float sphere::getRadius(){
	return this->radius;
}

/*
Returns the sphere's center point
*/
Vector3f sphere::getCenter(){
	return this->center;
}

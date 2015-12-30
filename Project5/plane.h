#pragma once
#include "Vector3f.h"
#include "ray.h"
#include <math.h>
#include "shape.h"

class plane : public shape
{


protected:
	float shininess;
public:
	Vector3f ka;
	Vector3f kd;
	Vector3f ks;
	Vector3f normal;
	Vector3f point;

	plane(Vector3f Normal, Vector3f Point, Vector3f Ka, Vector3f Kd, Vector3f Ks, float shininess);
	~plane(void);
	float intersection(ray* r);
	Vector3f getNormal(Vector3f p);
	Vector3f plane::getPoint();
	Vector3f plane::getCenter();
};
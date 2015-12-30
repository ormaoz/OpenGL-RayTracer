#pragma once
#include "Vector3f.h"
#include "ray.h"
#include <math.h>
#include "shape.h"

class sphere : public shape
{


private:
	float radius;
	float shininess;
	Vector3f center; //center of mass

public:
	Vector3f ka;
	Vector3f kd;
	Vector3f ks;
	Vector3f intersectionPoint;

	sphere(Vector3f Center, float Radius, Vector3f Ka, Vector3f Kd, Vector3f Ks, float Shininess);
	~sphere(void);
	float intersection(ray* r);
	Vector3f getNormal(Vector3f p);
	float getRadius();
	void setRadius(float radius);
	Vector3f getCenter();
	void setCenter(Vector3f center);

};
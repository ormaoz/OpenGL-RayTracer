#pragma once
#include <math.h>
#include "Vector3f.h"
#include "ray.h"

class shape
{
protected:
	Vector3f color;
public:
	Vector3f ka;
	Vector3f kd;
	Vector3f ks;
	int		 shininess;

	shape(Vector3f Ka, Vector3f Kd, Vector3f Ks, int shininess) {
		this->ka = Ka;
		this->kd = Kd;
		this->ks = Ks;
		this->shininess = shininess;

	};
	virtual float intersection(ray* r) = 0;
	virtual	Vector3f getNormal(Vector3f p) = 0;
};

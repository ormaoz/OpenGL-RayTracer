#pragma once
#include "Vector3f.h"
class ray
{
private:
	Vector3f point;
	Vector3f direction;
public:
	bool minusDiscriminent = false;

	ray(Vector3f point, Vector3f direction); 
	
	Vector3f getPoint();
	Vector3f getDirection();
	void setMinusDiscriminent(bool setMinus);
	~ray();

	
};


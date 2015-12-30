#pragma once
#include "Vector3f.h"


class light
{
private:
	Vector3f p; //position
	Vector3f v; //direction
	Vector3f in; //intensity
	float angle;
public:
	bool isSpotlight;
	light(Vector3f direction, Vector3f I);
	light(Vector3f direction, Vector3f I, Vector3f point, float cutOff);
	Vector3f calculatePixValue(Vector3f Ka, Vector3f Kd, Vector3f Ks, Vector3f normal, Vector3f viewer, int power);
	Vector3f light::calculateSpotlightPixValue(Vector3f Ka, Vector3f Kd, Vector3f Ks, Vector3f normal, Vector3f viewer, int power, float cosAngle, Vector3f direction);
	Vector3f getPosition();
	Vector3f getDirection();
	Vector3f getIntensity();
	float light::getAngle();
};
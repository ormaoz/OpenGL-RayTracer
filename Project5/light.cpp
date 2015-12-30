#include "light.h"

/*
Constructor
*/
light::light(Vector3f direction, Vector3f I)
{
	p = direction;
	v = direction;
	v.normalize();
	in = I;
	angle = 0;
	isSpotlight = false;
}
/*
Constructor for spotlight
*/
light::light(Vector3f direction, Vector3f I, Vector3f position, float cutOff)
{
	p = position;
	v = direction;
	v.normalize();
	in = I;
	angle = cutOff;
	isSpotlight = true;
}

/* Calculate the value of a pixel accroding to the Ka, Kd and Ks for every light but spotlight*/
Vector3f light::calculatePixValue(Vector3f Ka, Vector3f Kd, Vector3f Ks, Vector3f normal, Vector3f viewer, int power)
{
	Vector3f res(0, 0, 0);
	Vector3f r = -v + 2 * v.dotProduct(v, normal)*normal; //reflected ray from surface 
	r.normalize();
	float cosAlpha = viewer.dotProduct(viewer, r);
	float cosTheta = v.dotProduct(normal, v);
	if (cosAlpha > 0 && power > 0) {
		if (cosTheta > 0) {
			res = Kd*in*cosTheta + Ks*in*pow(cosAlpha, power);
		}
		else {
			res = Ks*in*pow(cosAlpha, power);
		}
	}
	else if (cosTheta>0) {
		res = Kd*in*cosTheta;
	}
	return res;
}

/* Calculate the value of a pixel accroding to the Ka, Kd and Ks for spotlight*/
Vector3f light::calculateSpotlightPixValue(Vector3f Ka, Vector3f Kd, Vector3f Ks, Vector3f normal, Vector3f viewer, int power, float cosAngle, Vector3f direction)
{
	Vector3f res(0, 0, 0);
	// Since it's a spotlight - calculate r using the vector from the light to the pixel
	Vector3f r = -direction + 2 * direction.dotProduct(direction, normal)*normal; //reflected ray from surface 
	r.normalize();
	float cosAlpha = viewer.dotProduct(viewer, r);
	float cosTheta = v.dotProduct(normal, v);
	if (cosAlpha > 0 && power > 0) {
		if (cosTheta > 0) {
			// Since it's a spotlight - multiply the intensity by the angle from the light direction
			res = Kd*in*cosAngle*cosTheta + Ks*in*cosAngle*pow(cosAlpha, power);
		}
		else {
			res = Ks*in*cosAngle*pow(cosAlpha, power);
		}
	}
	else if (cosTheta>0) {
		res = Kd*in*cosAngle*cosTheta;
	}
	return res;
}

Vector3f light::getPosition() {
	if (isSpotlight) {
		return this->p;
	}
	else {
		return Vector3f(0,0,0);
	}
}
Vector3f light::getDirection(){
	return this->v;
}
Vector3f light::getIntensity() {
	return this->in;
}

float light::getAngle() {
	if (isSpotlight) {
		return this->angle;
	}
	else {
		return 0;
	}
	
}
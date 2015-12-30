#pragma once
#include <stdio.h>
#include <vector>
#include "glut.h"
#include "Vector3f.h"
#include "Ray.h"
#include "sphere.h"
#include "plane.h"
#include "light.h"
#include <iostream>

using namespace std;

class scene
{
public:
	Vector3f screenCenter, upVector, backgroundColor;
	int width, resWidth, resHeight, screenWidth;


	Vector3f bgColor;
	vector<sphere*> sphere;
	vector<plane*> plane;
	vector<light*> light;

//public:
	Vector3f aLightning;
	scene(Vector3f screenCenter, Vector3f upVector, int screenWidth, int resWidth, int resHeight, Vector3f ambientLightning, Vector3f backgroundColor);
	~scene(void);


};
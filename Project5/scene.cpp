#include <stdio.h>
#include <Windows.h>
#include "scene.h"
#include "Vector3f.h"
#include "Ray.h"
#include "sphere.h"
#include "plane.h"


using namespace std;
#pragma once

/*
Constructor
*/
scene::scene(Vector3f screenCenter, Vector3f upVector, int screenWidth, int resWidth, int resHeight, Vector3f ambientLightning, Vector3f backgroundColor) {
	this->screenCenter = screenCenter;
	this->resWidth = resWidth;
	this->resHeight = resHeight;
	this->aLightning = ambientLightning;
	this->backgroundColor = backgroundColor;
	this->upVector = upVector;
	this->screenWidth = screenWidth;
}

scene::~scene(void){

}
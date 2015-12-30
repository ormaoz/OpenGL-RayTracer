#pragma once
#include <stdio.h>
#include "glut.h"
#include "Vector3f.h"
#include "light.h"
#include "plane.h"
#include "sphere.h"
#include "scene.h"

using namespace std;

class fileParse {

public:
	FILE *input;
	vector<shape*> shapes;
	vector<light*> lights;
	scene* scn;

	fileParse(FILE *input);
	~fileParse(void);

	void parser();
	vector<shape*> getShapes();
	vector<light*> getLights();
	scene* getScene();
};
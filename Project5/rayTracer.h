#pragma once
#include "shape.h"
#include "scene.h"

using namespace std;

class rayTracer
{
public:
	GLubyte *scenePic;
	GLint width;
	GLint height;
	GLuint texture[2];
	vector <light*> lights;
	vector <shape*> shapes;
	scene* theScene;
	Vector3f up;
	Vector3f screenCenter;
	float screenWidth;

	bool hasShadow(Vector3f direction);

	void readFile();

	void buildScene();

	void init();

	void mydisplay();

	int main(int  argc, char** argv);
};
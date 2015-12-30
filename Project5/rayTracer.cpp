#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "glut.h"
#include "ray.h"
#include "sphere.h"
#include "plane.h"
#include "light.h"
#include "scene.h"
#include "fileParse.h"

using namespace std;
#define PI	3.141592 

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

/*
Checks if a certain point is hidden in the shadow by a diffrent shape
*/
bool hasShadow(Vector3f direction, shape* closestShape, Vector3f intersectionPoint) {
	ray* ray2Light = new ray(intersectionPoint, -direction);
	bool isShadow;
	for (shape* ashape : shapes)
	{
		if (ashape != closestShape) {
			float t = ashape->intersection(ray2Light);
			if (t < FLT_MAX){
				isShadow = true;
				break;
			}
		}
		else {
			isShadow = false;
		}
	}
	return isShadow;
}

/*
Read the file using file
*/
void readFile() {
	// Open the input file
	FILE* input;
	input = fopen("scene.txt", "r");

	// Parse the parameters of the files
	fileParse* parse = new fileParse(input);
	parse->parser();
	
	// Save all diffrenet objects into arrays
	lights = parse->getLights();
	shapes = parse->getShapes();
	theScene = parse->getScene();
	
	// Save data from scene to the members
	width = theScene->resWidth;
	height = theScene->resHeight;
	up = theScene->upVector;
	screenCenter = theScene->screenCenter;
	screenWidth = theScene->screenWidth;
}

void buildScene()
{
	Vector3f eyePosition(0, 0, 0);    //P0
	Vector3f right(1, 0, 0);

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {

			// Calculate the ray for each pixel
			Vector3f rightDirection = (float)((i - width / 2.0) / width * screenWidth) * right;
			Vector3f upDirection = (float)((j - height / 2.0) / width * screenWidth) * up;
			ray* r = new ray(eyePosition, (screenCenter + rightDirection + upDirection) - eyePosition);

			float t;

			// Find the min distance for the objects for each pixel
			float minT = FLT_MAX;
			shape* closestShape = NULL;
			for (shape* shape : shapes) {
				t = shape->intersection(r);
				if (t < minT) {
					minT = t;
					closestShape = shape;
				}
			}

			Vector3f color(0, 0, 0);

			// In case there is some intersection with some shape
			if (closestShape != NULL) {

				// Calculate ambient lightning once for each shape.
				color += closestShape->ka * theScene->aLightning;

				// For every light in the scene
				for (light* currentLight : lights) {

					// Calculate the intersection point between plane and light ray
					Vector3f intersectionPoint = eyePosition + r->getDirection()*minT; 

					// Calculate the normal to the shape
					Vector3f normal = closestShape->getNormal(intersectionPoint);
					
					if (r->minusDiscriminent) {
						normal = -normal;
					}

					// In case the light is a spotlight
					if (currentLight->isSpotlight) {
						
						// Calculate the vector between the current point and light origin
						Vector3f lightVector2Point = intersectionPoint - currentLight->getPosition();
						lightVector2Point.normalize();

						// Calculate the cosine angle between the light direction and light vector to point 
						float angleToPoint = lightVector2Point.dotProduct(lightVector2Point, currentLight->getDirection());

						// Calculate the cosine of the spotlight angle
						float cosCutOff = cos(PI * currentLight->getAngle() / 180.0);

						// Checks if the the angle to the point is smaller than the spotlight angle. if it is, calculate pixel value, if it's not, skip to the next light.
						if (angleToPoint <= cosCutOff) {	
							continue;
						}
						else {
							// Check if the point is covered by shadow
							if (hasShadow(lightVector2Point, closestShape, intersectionPoint)){
								color += Vector3f(0,0,0);
							}
							else {
								color += currentLight->calculateSpotlightPixValue(closestShape->ka, closestShape->kd, closestShape->ks, normal, r->getDirection(), closestShape->shininess, angleToPoint, lightVector2Point);
							}
							if (color.x>1)
								color.x = 1;

							if (color.y>1)
								color.y = 1;

							if (color.z>1)
								color.z = 1;
							scenePic[i * 3 + j*width * 3] = color.x*255.0;
							scenePic[i * 3 + j*width * 3 + 1] = color.y*255.0;
							scenePic[i * 3 + j*width * 3 + 2] = color.z*255.0;
						}
						
					// In case the light is not a spotlight
					}
					else{
						// Check if the point is covered by shadow
						if (hasShadow(currentLight->getDirection(), closestShape, intersectionPoint)) {
							color += Vector3f(0, 0, 0);
						}
						else {
							color += currentLight->calculatePixValue(closestShape->ka, closestShape->kd, closestShape->ks, normal, r->getDirection(), closestShape->shininess);
						}
						if (color.x>1)
							color.x = 1;

						if (color.y>1)
							color.y = 1;

						if (color.z>1)
							color.z = 1;

						scenePic[i * 3 + j*width * 3] = color.x*255.0;
						scenePic[i * 3 + j*width * 3 + 1] = color.y*255.0;
						scenePic[i * 3 + j*width * 3 + 2] = color.z*255.0;
					}	
				}	
			}
			// In case there is no intersection, color pixel black
			else {
				scenePic[i * 3 + j*width * 3] = theScene->backgroundColor.x;
				scenePic[i * 3 + j*width * 3 + 1] = theScene->backgroundColor.y;
				scenePic[i * 3 + j*width * 3 + 2] = theScene->backgroundColor.z;
			}
		}
	}
}

void init()
{
	readFile();
	glEnable(GL_TEXTURE_2D);
	glOrtho(-1.0, 1.0, -1.0, 1.0, 2.0, -2.0);
	glClearColor(0, 0, 0, 0);
	//glLoadIdentity();
	//gluPerspective(atan(0.5)*180/M_PI,1,2,8);
	glMatrixMode(GL_MODELVIEW);

	scenePic = new GLubyte[width*height * 3];
	buildScene();

	glGenTextures(1, &texture[0]);  //generate place for new texture
	glBindTexture(GL_TEXTURE_2D, texture[0]); // initialize first texure 

	//texture properties
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	//build texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, scenePic);
}

void mydisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, texture[0]); //using first texture
	glViewport(0, 0, 512, 512);
	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);

	glTexCoord2f(0, 0); //adapt texture to shape
	glVertex3f(-1.0, -1.0f, 0);

	glTexCoord2f(1, 0);  //adapt texture to shape
	glVertex3f(1.0, -1.0f, 0);

	glTexCoord2f(1, 1);//adapt texture to shape
	glVertex3f(1.0, 1.0f, 0);

	glTexCoord2f(0, 1);//adapt texture to shape
	glVertex3f(-1.0, 1.0f, 0);

	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
	glFlush();
}

int main(int  argc, char** argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(512, 512);
	glutCreateWindow("Simple");
	init();
	// glutReshapeFunc(myReshape);
	glutDisplayFunc(mydisplay);
	//glutIdleFunc(mydisplay);

	glutMainLoop();
	delete scenePic;
}
#include "fileParse.h"

using namespace std;

/*
Constructor
*/
fileParse::fileParse(FILE *input) {
	this->input = input;

}

// Distrcutor
fileParse::~fileParse() {

}

/*
Parse the data of the file according to the keywords
*/
void fileParse::parser() {

	Vector3f pc, upVector, aLightning, bgColor;
	int width, rx, ry;

	// Read all the parameters
	fseek(input, 5, SEEK_CUR); //skip 5 character from the current position in the file ("Scene")
	fscanf(input, "%f,%f,%f,", &pc.x, &pc.y, &pc.z);
	fscanf(input, "%f,%f,%f,", &upVector.x, &upVector.y, &upVector.z);
	fscanf(input, "%d,%d,%d,", &width, &rx, &ry);
	fscanf(input, "%f,%f,%f,", &aLightning.x, &aLightning.y, &aLightning.z);
	fscanf(input, "%f,%f,%f\n", &bgColor.x, &bgColor.y, &bgColor.z);

	// Create the scene
	this->scn = new scene(pc, upVector, width, rx, ry, aLightning, bgColor);
	
	// String to store the keyword
	char keyword[CHAR_MAX];

	// Keep trying reading from the file as long as the keyword is not null
	while (fscanf(input, "%s ", keyword) != EOF) {
		
		// In case the keyword is sphere (spher)
		if (strcmp(keyword, "spher") == 0) {
			
			float radius, shininess;
			Vector3f center, ka, kd, ks;

			// Read all the parameters
			fscanf(input, "%f,%f,%f,", &center.x, &center.y, &center.z);
			fscanf(input, "%f,", &radius);
			fscanf(input, "%f,%f,%f,", &ka.x, &ka.y, &ka.z);
			fscanf(input, "%f,%f,%f,", &kd.x, &kd.y, &kd.z);
			fscanf(input, "%f,%f,%f,", &ks.x, &ks.y, &ks.z);
			fscanf(input, "%f\n", &shininess);

			// create the sphere accrording to the parametes and push it to the sphere array
			shapes.push_back(new sphere(center, radius, ka, kd, ks, shininess));

		}
		// In case the keyword is plane
		else if (strcmp(keyword, "plane") == 0) {

			Vector3f normal, point, ka, kd, ks;
			float shininess;

			// Read all the parameters
			fscanf(input, "%f,%f,%f,", &normal.x, &normal.y, &normal.z);
			fscanf(input, "%f,%f,%f,", &point.x, &point.y, &point.z);
			fscanf(input, "%f,%f,%f,", &ka.x, &ka.y, &ka.z);
			fscanf(input, "%f,%f,%f,", &kd.x, &kd.y, &kd.z);
			fscanf(input, "%f,%f,%f,", &ks.x, &ks.y, &ks.z);
			fscanf(input, "%f\n", &shininess);

			// create the sphere accrording to the parametes and push it to the sphere array
			shapes.push_back(new plane(normal, point, ka, kd, ks, shininess));
		}
		// In case the keyword is light
		else if (strcmp(keyword, "light") == 0) {

			float cutoffAngle;
			Vector3f direction, intensity, position;

			// Read all the parameters
			fscanf(input, "%f,%f,%f,", &direction.x, &direction.y, &direction.z);
			fscanf(input, "%f,%f,%f", &intensity.x, &intensity.y, &intensity.z);


			// In case it's a spotlight, continue reading.
			char isSpotlight;
			fscanf(input, "%c", &isSpotlight);
			if (isSpotlight != '\n') {
				fscanf(input, "%f,%f,%f,", &position.x, &position.y, &position.z);
				fscanf(input, "%f\n", &cutoffAngle);

				// Create the spotlight accrording to the parametes and push it to the lights array
				lights.push_back(new light(direction, intensity, position, cutoffAngle));
			}
			else {
				// create the light accrording to the parametes and push it to the lights array
				lights.push_back(new light(direction, intensity));
			}
		}
	}
}
	
/*
Return the shapes array
*/
vector<shape*> fileParse::getShapes() {
	return shapes;
}

/*
Return the lights array
*/
vector<light*> fileParse::getLights() {
	return lights;
}

/*
Return the scene
*/
scene* fileParse::getScene() {
	return this->scn;
}
#include <cmath>
#include "constants.h"

//FOV = 1 / tan(angle/2)
//in this case its 90 degrees
const float ANGLE = 90.0f;
const float FOV = 0.61736962f;

float Dot(float threeVec[3], float val) {
	return val * (threeVec[0] + threeVec[1] + threeVec[2]);
}
float Dot(const float threeVecConst[3], float val) {
	return val * (threeVecConst[0] + threeVecConst[1] + threeVecConst[2]);
}
float Dot(float val, float threeVec[3]) {
	return Dot(threeVec, val);
}


const float MIN_X_3D = -1.0f;
const float MAX_X_3D = 1.0f;
const float MIN_Y_3D = -1.0f;
const float MAX_Y_3D = 1.0f;
const float MIN_Z_3D = -1.0f;
const float MAX_Z_3D = 1.0f;
//camera rotation
const float FOCAL_LENGTH = 1.0f;
//rotation matrix
const float CAMERA_ROTATION[3][3] = {
	{0,0,0},
	{0,0,0},
	{0,0,0}
};
const float CAMERA_PX = 0;
const float CAMERA_PY = 0;
//translation vector
const float CAMERA_TRANSLATION[3] = {0,0,0};

//you multiply (xPos,yPos,zPos,1) by this matrix on the left
//to get to 2d plane coordinates
//then normalize said plane coordinates somehow
void* GetCameraMatrix(float f, float PX, float PY, float R[3][3], float T[3]) {
	float cam[3][4];
	cam[0][0] = f * R[0][0] + PX * R[2][0];
	cam[0][1] = f * R[0][1] + PX * R[2][1];
	cam[0][2] = f * R[0][2] + PX * R[2][2];
	cam[0][3] = f * T[0] + PX * T[2];

	cam[1][0] = f * R[1][0] + PY * R[2][0];
	cam[1][1] = f * R[1][1] + PY * R[2][1];
	cam[1][2] = f * R[1][2] + PY * R[2][2];
	cam[1][3] = f * T[1] + PY * T[2];

	cam[2][0] = R[2][0];
	cam[2][1] = R[2][1];
	cam[2][2] = R[2][2];
	cam[2][3] = T[2];

	return &cam;
}

void GetPixelsFrom3d(float xPos, float yPos, float zPos, float* xPix, float* yPix) {
	
}

void VoxelTest3d() {
	float dx = 0.1f;
	float dy = 0.1f;
	float dz = 0.1f;
	for (float xPos = MIN_X_3D; xPos < MAX_X_3D; xPos += dx) {
		for (float yPos = MIN_Y_3D; yPos < MAX_Y_3D; yPos += dy) {
			for (float zPos = MIN_Z_3D; zPos < MAX_Z_3D; zPos += dz) {
				if (xPos + yPos + zPos <= 1.0f) {
					//todo something

				}
			}
		}
	}
}
/*
 * Camera.h
 *
 *  Created on: Feb 11, 2020
 *      Author: MihailRis
 */

#ifndef WINDOW_CAMERA_H_
#define WINDOW_CAMERA_H_

#include "../glm/glm.hpp"
using namespace glm;

class Camera {
	void updateVectors();
public:
	vec3 front;
	vec3 up;
	vec3 right;
	vec3 dir;

	vec3 position;
	float fov;
	float zoom;
	mat4 rotation;
	Camera(vec3 position, float fov);

	void process(float speed, float delta);
	void processRotation();
	vec3 findDirent();
	void rotate(float x, float y, float z);
	void setPos(float x, float y, float z);
	vec3 getPos();
	int getDistanceFromPoint(int X, int Y, int Z);

	mat4 getProjection();
	mat4 getView();
};

#endif /* WINDOW_CAMERA_H_ */

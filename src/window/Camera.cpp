/*
 * Camera.cpp
 *
 *  Created on: Feb 11, 2020
 *      Author: MihailRis
 */

#include "Camera.h"
#include "Window.h"
#include "Events.h"
#include "../physics/Hitbox.h"

#include "../glm/ext.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

Camera::Camera(vec3 position, float fov) : position(position), fov(fov), zoom(1.0f), rotation(1.0f) {
	updateVectors();
}

extern Hitbox* hitbox;
extern bool bIgnoreControllable;
void Camera::process(float speed, float delta)
{
	bool sprint = Events::pressed(GLFW_KEY_LEFT_CONTROL) && !bIgnoreControllable;
	bool shift = Events::pressed(GLFW_KEY_LEFT_SHIFT) && hitbox->grounded && !sprint && !bIgnoreControllable;

	this->setPos(hitbox->position.x, hitbox->position.y + 0.5f, hitbox->position.z);

	float dt = min(1.0f, delta * 16);
	if (shift)
	{
		speed *= 0.25f;
		this->position.y -= 0.2f;
		this->zoom = 0.9f * dt + this->zoom * (1.0f - dt);
	} 
	else if (sprint)
	{
		speed *= 1.5f;
		this->zoom = 1.1f * dt + this->zoom * (1.0f - dt);
	} 
	else 
	{
		this->zoom = dt + this->zoom * (1.0f - dt);
	}
}

float camX = 0.0f;
float camY = 0.0f;

void Camera::processRotation()
{
	camY += -Events::deltaY / Window::height * 2;
	camX += -Events::deltaX / Window::height * 2;

	if (camY < -radians(89.0f)){
		camY = -radians(89.0f);
	}

	if (camY > radians(89.0f)){
		camY = radians(89.0f);
	}

	this->rotation = mat4(1.0f);
	this->rotate(camY, camX, 0);
}

void Camera::setPos(float x, float y, float z)
{
	this->position.x = x;
	this->position.y = y;
	this->position.z = z;
}

vec3 Camera::getPos()
{
	return this->position;
}

#include <cmath>
int Camera::getDistanceFromPoint(int X, int Y, int Z)
{
	int fSX = 0.0f, fSY = 0.0f, fSZ = 0.0f;

	fSX = (this->position.x - X) * (this->position.x - X);
	fSY = (this->position.y - Y) * (this->position.y - Y);
	fSZ = (this->position.z - Z) * (this->position.z - Z);
	
	return (int)sqrt(fSX + fSY + fSZ);
}

vec3 Camera::findDirent()
{
	vec3 dir(0,0,0);

	if (Events::pressed(GLFW_KEY_W) && !bIgnoreControllable){
		dir.x += this->dir.x;
		dir.z += this->dir.z;
	}

	if (Events::pressed(GLFW_KEY_S) && !bIgnoreControllable){
		dir.x -= this->dir.x;
		dir.z -= this->dir.z;
	}

	if (Events::pressed(GLFW_KEY_D) && !bIgnoreControllable){
		dir.x += this->right.x;
		dir.z += this->right.z;
	}

	if (Events::pressed(GLFW_KEY_A) && !bIgnoreControllable){
		dir.x -= this->right.x;
		dir.z -= this->right.z;
	}
	
	if (length(dir) > 0.0f) {
		dir = normalize(dir);
	}

	return dir;
}

void Camera::updateVectors(){
	front = vec3(rotation * vec4(0,0,-1,1));
	right = vec3(rotation * vec4(1,0,0,1));
	up = vec3(rotation * vec4(0,1,0,1));
	dir = vec3(rotation * vec4(0,0,-1,1));
	dir.y = 0;
	float len = length(dir);
	if (len > 0.0f){
		dir.x /= len;
		dir.z /= len;
	}
}

void Camera::rotate(float x, float y, float z){
	rotation = glm::rotate(rotation, z, vec3(0,0,1));
	rotation = glm::rotate(rotation, y, vec3(0,1,0));
	rotation = glm::rotate(rotation, x, vec3(1,0,0));

	updateVectors();
}

mat4 Camera::getProjection(){
	float aspect = (float)Window::width / (float)Window::height;
	return glm::perspective(fov*zoom, aspect, 0.05f, 1500.0f);
}

mat4 Camera::getView(){
	return glm::lookAt(position, position+front, up);
}

#include "../Utility/stdafx.h"
#include "Camera.h"

using namespace Model;

Camera::Camera()
{
}

Camera::Camera(Vector3 _position, Vector3 _centerOfInterest, Vector3 _userUpVector)
	: position(_position), centerOfInterest(_centerOfInterest), userUpVector(_userUpVector)
{
}

void Camera::initialize()
{
	viewVector = centerOfInterest.subtract(position);
	sideVector = viewVector.crossProduct(userUpVector);
	upVector = sideVector.crossProduct(viewVector);

	viewVector = viewVector.normalize();
	sideVector = sideVector.normalize();
	upVector = upVector.normalize();
}

Vector3 Camera::GetPosition(){ return position; }
Vector3 Camera::GetCenterOfInterest(){ return centerOfInterest; }
Vector3 Camera::GetUserUpVector(){ return userUpVector; }
Vector3 Camera::GetViewVector(){ return viewVector; } 
Vector3 Camera::GetSideVector(){ return sideVector; }
Vector3 Camera::GetUpVector(){ return upVector; }
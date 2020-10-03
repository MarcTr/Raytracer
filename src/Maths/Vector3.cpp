#include "../Utility/stdafx.h"
#include "Vector3.h"
#include <cmath>

using namespace Maths;

Vector3::Vector3()
{
}

Vector3::Vector3(double _x, double _y, double _z)
	: x(_x), y(_y), z(_z)
{
}

Vector3 Vector3::subtract(Vector3 v)
{
	double xResult = this->x - v.x;
	double yResult = this->y - v.y;
	double zResult = this->z - v.z;

	return Vector3(xResult, yResult, zResult);
}

Vector3 Vector3::add(Vector3 v)
{
	double xResult = this->x + v.x;
	double yResult = this->y + v.y;
	double zResult = this->z + v.z;

	return Vector3(xResult, yResult, zResult);
}

double Vector3::scalarProduct(Vector3 v)
{
	return this->x * v.x + this->y * v.y + this->z * v.z;
}

Vector3 Vector3::multiply(double scalar)
{
	double xResult = this->x * scalar;
	double yResult = this->y * scalar;
	double zResult = this->z * scalar;

	return Vector3(xResult, yResult, zResult);

}

Vector3 Vector3::crossProduct(Vector3 v)
{
	double xResult = this->y * v.z - this->z * v.y;
	double yResult = this->z * v.x - this->x * v.z;
	double zResult = this->x * v.y - this->y * v.x;

	return Vector3(xResult, yResult, zResult);
}

double Vector3::magnitude()
{
	return std::sqrt(std::pow(this->x, 2) 
					+ std::pow(this->y, 2) 
					+ std::pow(this->z, 2));
}


Vector3 Vector3::normalize()
{
	double magnitude = this->magnitude();
	return Vector3(this->x / magnitude, this->y / magnitude, this->z / magnitude);
}


std::string Vector3::toString()
{
	return "(" + std::to_string(x) + ", "
			+ std::to_string(y) + ", "
			+ std::to_string(z) + ")";
}

double Vector3::getX() { return x; }
double Vector3::getY() { return y; }
double Vector3::getZ() { return z; }

void Vector3::setX(double _x) { this->x = _x; }
void Vector3::setY(double _y) { this->y = _y; }
void Vector3::setZ(double _z) { this->z = _z; }
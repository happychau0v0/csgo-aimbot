#include "vector3.h"

vector3::vector3() {
	x = y = z = 0;
}

vector3::vector3(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

vector3& vector3::operator+(vector3 arg) {
	x += arg.x;
	y += arg.y;
	z += arg.z;
	return *this;
}

vector3& vector3::operator-(vector3 arg) {
	x -= arg.x;
	y -= arg.y;
	z -= arg.z;
	return *this;
}

vector3& vector3::operator*(float arg) {
	x *= arg;
	y *= arg;
	z *= arg;
	return *this;
}

void vector3::normalize() {
	while (this->x < -89)
		this->x = -89;
	while (this->x > 89)
		this->x = 89;
	while (this->y < -180)
		this->y += 180;
	while (this->y > 180)
		this->y -= 180;
}
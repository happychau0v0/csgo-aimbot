#pragma once

class vector3 {
public:
	float x, y, z;

	vector3() {
		x = y = z = 0;
	}

	vector3(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	vector3& operator+(vector3 arg) {
		x += arg.x;
		y += arg.y;
		z += arg.z;
		return *this;
	}
};
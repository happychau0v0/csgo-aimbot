#pragma once

class vector3 {
public:
	float x, y, z;

	vector3();
	vector3(float, float, float);

	vector3& operator+(vector3);
	vector3& operator-(vector3);
	vector3& operator*(float);
	
	void normalize();
};
#pragma once

class vector3;

class localPlayer {

private:
	localPlayer();

public:
	static localPlayer* get();

	vector3* getOrigin();
	vector3* getViewOffset();
	int* getHealth();
	int* getTeam();
	void aimAt(vector3* target);
	float getDistance(vector3*);
};
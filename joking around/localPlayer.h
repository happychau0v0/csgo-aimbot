#pragma once
#include "vector3.h"

class localPlayer {

private:
	localPlayer();

public:
	static localPlayer* get();

	vector3* getOrigin();
	vector3* getViewOffset();
	vector3* aimPunchAngle();
	int* iShotsFired();
	int* getHealth();
	int* getTeam();
	float getDistance(vector3*);

	void aimAt(vector3*);
};
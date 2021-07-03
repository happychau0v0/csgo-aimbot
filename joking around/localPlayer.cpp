#include "localPlayer.h"
#include "offsets.h"
#include "vector3.h"
#include <cstdint>
#include <Windows.h>
#include <math.h>
#include <iostream>

localPlayer* localPlayer::get() {
	static uint32_t clientModule = (uint32_t)(GetModuleHandle("client.dll"));
	static localPlayer* player = (localPlayer*)(clientModule + hazedumper::signatures::dwLocalPlayer);

	return player;
}

vector3* localPlayer::getOrigin() {
	return (vector3*)(*(uintptr_t*)this + hazedumper::netvars::m_vecOrigin);
}

vector3* localPlayer::getViewOffset() {
	return (vector3*)(*(uintptr_t*)this + hazedumper::netvars::m_vecViewOffset);
}

int* localPlayer::getHealth() {
	return (int*)(*(uintptr_t*)this + hazedumper::netvars::m_iHealth);
}

int* localPlayer::getTeam() {
	return (int*)(*(uintptr_t*)this + hazedumper::netvars::m_iTeamNum);
}

float localPlayer::getDistance(vector3* other) {
	vector3* myPos = getOrigin();
	vector3 delta(myPos->x - other->x, myPos->y - other->y, myPos->z - other->z);

	return sqrt(delta.x * delta.x + delta.y * delta.y + delta.z * delta.z);
}

const double PI = 3.14159265359;
static vector3 oPunch, recoil;
float cooldown = 1;

void localPlayer::aimAt(vector3* target) {
	static uint32_t engineModule = (uint32_t)GetModuleHandle("engine.dll");
	static vector3* viewAngles = (vector3*)(*(uint32_t*)(engineModule + hazedumper::signatures::dwClientState) + hazedumper::signatures::dwClientState_ViewAngles);

	vector3 origin = *getOrigin();
	vector3 viewOffset = *getViewOffset();
	vector3* myPos = &(origin + viewOffset);

	vector3 delta = *target - *myPos;
	float len = sqrt(delta.x * delta.x + delta.y * delta.y + delta.z * delta.z);

	vector3 change(-asin(delta.z / len) * 180 / PI, atan2(delta.y, delta.x) * 180 / PI, 0);
	change = change - *viewAngles;

	vector3 punchAngle = *aimPunchAngle() * 2;

	if (*iShotsFired() > 1) {
		recoil = recoil + oPunch - punchAngle;
		cooldown = 1;
	}
	else {
		recoil = recoil * pow(cooldown, 2.65);
		if (cooldown > 0.1) cooldown -= 0.0007;
	}

	recoil.normalize();
	change = change + recoil;
	change.normalize();

	//std::cout << recoil.x << ' ' << recoil.y << ' ' << recoil.z << std::endl;

	oPunch = punchAngle;

	if (GetAsyncKeyState(VK_LBUTTON)) *viewAngles = *viewAngles + change;
	
}

vector3* localPlayer::aimPunchAngle() {
	return (vector3*)(*(uintptr_t*)this + hazedumper::netvars::m_aimPunchAngle);
}

int* localPlayer::iShotsFired() {
	return (int*)(*(uintptr_t*)this + hazedumper::netvars::m_iShotsFired);
}
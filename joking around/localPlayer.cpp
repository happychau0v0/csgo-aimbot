#include "localPlayer.h"
#include "offsets.h"
#include "vector3.h"
#include <cstdint>
#include <Windows.h>
#include <math.h>

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

void localPlayer::aimAt(vector3* target) {
	static uint32_t engineModule = (uint32_t)GetModuleHandle("engine.dll");
	static vector3* viewAngles = (vector3*)(*(uint32_t*)(engineModule + hazedumper::signatures::dwClientState) + hazedumper::signatures::dwClientState_ViewAngles);

	vector3 origin = *getOrigin();
	vector3 viewOffset = *getViewOffset();
	vector3* myPos = &(origin + viewOffset);

	vector3 delta(target->x - myPos->x, target->y - myPos->y, target->z - myPos->z);
	float len = sqrt(delta.x * delta.x + delta.y * delta.y + delta.z * delta.z);

	float pitch = -asin(delta.z / len) * 180 / PI;
	float yaw = atan2(delta.y, delta.x) * 180 / PI;

	if (pitch >= -89 && pitch <= 89 && yaw >= -180 && yaw <= 180) {
		viewAngles->x = pitch;
		viewAngles->y = yaw;
	}
}
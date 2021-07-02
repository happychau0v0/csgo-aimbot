#include "player.h"
#include "offsets.h"
#include "vector3.h"
#include <cstdint>
#include <Windows.h>

player* player::getPlayer(int index) {
	static uint32_t moduleBase = (uint32_t)GetModuleHandle("client.dll");
	static uint32_t entityList = moduleBase + hazedumper::signatures::dwEntityList;

	return (player*)(entityList + index * 0x10);
}

int* player::getMaxPlayer() {
	static uint32_t moduleBase = (uintptr_t)GetModuleHandle("Engine.dll");
	return (int*)(*(uint32_t*)(moduleBase + hazedumper::signatures::dwClientState) + hazedumper::signatures::dwClientState_MaxPlayer);
}

vector3* player::getOrigin() {
	return (vector3*)(*(uintptr_t*)this + hazedumper::netvars::m_vecOrigin);
}

vector3* player::getViewOffset() {
	return (vector3*)(*(uintptr_t*)(this + hazedumper::netvars::m_vecViewOffset));
}

vector3* player::getBonePos(int boneID) {
	uint32_t boneMatrix = *(uint32_t*)(*(uint32_t*)this + hazedumper::netvars::m_dwBoneMatrix);
	static vector3 bonePos;
	bonePos.x = *(float*)(boneMatrix + 0x30 * boneID + 0x0C);
	bonePos.y = *(float*)(boneMatrix + 0x30 * boneID + 0x1C);
	bonePos.z = *(float*)(boneMatrix + 0x30 * boneID + 0x2C);
	return &bonePos;
}

int* player::getHealth() {
	return (int*)(*(uintptr_t*)this + hazedumper::netvars::m_iHealth);
}

int* player::getTeam() {
	return (int*)(*(uintptr_t*)this + hazedumper::netvars::m_iTeamNum);
}
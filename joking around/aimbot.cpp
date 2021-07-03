#include "localPlayer.h"
#include "player.h"
#include "vector3.h"
#include <cstdint>
#include <iostream>

player* getClosestEnemy() {
	localPlayer* me = localPlayer::get();
	float closestDist = 1000000;
	int index = -1;

	for (int i = 1; i < *player::getMaxPlayer(); i++) {
		player* cur = player::getPlayer(i);

		if (!cur || !(*(uint32_t*)cur) || (uint32_t)cur == (uint32_t)me)
			continue;
		
		if (*cur->getTeam() == *me->getTeam())
			continue;

		if (*cur->getHealth() < 1 || *me->getHealth() < 1)
			continue;

		float curDist = me->getDistance(cur->getOrigin());
		if (curDist < closestDist) {
			closestDist = curDist;
			index = i;
		}
	}

	if (index == -1) return NULL;
	return player::getPlayer(index);
}

void aimbot() {
	player* closestEnemy = getClosestEnemy();
	if (closestEnemy) {
		localPlayer::get()->aimAt(closestEnemy->getBonePos(8));
	}
}
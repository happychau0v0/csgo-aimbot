#pragma once

#pragma once

class vector3;

class player {

private:
	player();

public:
	static int* getMaxPlayer();
	static player* getPlayer(int index);

	int* getHealth();
	int* getTeam();
	vector3* getOrigin();
	vector3* getViewOffset();
	vector3* getBonePos(int boneID);

};
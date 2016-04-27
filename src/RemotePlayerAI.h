#pragma once
#include "RemotePlayer.h"
class RemotePlayerAI :
	public RemotePlayer
{
public:
	RemotePlayerAI();
	~RemotePlayerAI();

	bool connect();
	bool getReady();
	void update();
	void sendState(float axis_x, float axis_y, bool fire, bool hostTurn, bool lastShotHit);
	void sendGrid(PlayerData data);
	void sendPhys(float hostX, float hostY, float clientX, float clientY);
	PlayerData getGrid();
private:

	void newTarget();
	void doAI();

	// GAME STATE
	int playerX;
	int playerY;
	int ourX;
	int ourY;
	int turn;
	bool lastshothit;
	// AI STATE
	int * shotData = new int[100];	// 0 = no shot
									// 1 = miss
									// 2 = hit
	int targetX;
	int targetY;
	int shotX;
	int shotY;
	int mode; 	// 0 = hunt
				// 1 = kill
				// 2 = defend
	int oldMode;
	int shipDir;	// 0 = none/unknown
					// 1 = up/down
					// 2 = left/right
	int lastTurn;

	PlayerData data;
};


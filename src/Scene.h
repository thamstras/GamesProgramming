#pragma once
#include <vector>
#include <map>
#include <string>
#include <iostream>

#include "PhysObj.h"
#include "RenderObject.h"
#include "Sound.h"
#include "TextureManager.h"
#include "Structs.h"
#include "RemotePlayerAI.h"

enum SceneList
{
	SCENE_MENU, SCENE_TITLE, SCENE_INSTRUCTIONS, SCENE_PREGAME,
	SCENE_GAME_OURGRID, SCENE_GAME_THEIRGRID,
	SCENE_P1_WIN, SCENE_P2_WIN,
	SCENE_TEST_SCENE,
	SCENE_QUIT
};

class Scene
{
public:
	static Scene& getScene();
	
	std::vector<PhysObj *> PhysList;
	std::vector<RenderObject *> RenderList;

	std::vector<PhysObj *> PhysObjBuffer;
	std::vector<RenderObject *> RenderObjBuffer;
	bool listsLocked = false;

	std::map<std::string, std::string> SceneData;
	
	WorldBounds bounds = { 0, 0, 600, 600 };
	
	int gridWidth = 60;
	int gridHeight = 60;
	int gridOffsetX = 0;
	int gridOffsetY = 0;

	MouseData mouseData = { 0, 0, false, false };
	void updateMouseData(float x, float y, bool left, bool right);

	Sound* sound;
	TextureManager* textures;

	SceneList newScene;
	SceneList currentScene;

	float P1_axis_X = 0.0f;
	float p1_axis_Y = 0.0f;
	float p2_axis_X = 0.0f;
	float p2_axis_Y = 0.0f;

	int p1PosX = 0;
	int p1PosY = 0;
	int p2PosX = 0;
	int p2PosY = 0;
	bool ourTurn = false;
	bool lastShotHit = false;
	PlayerData p1Data;
	PlayerData p2Data;

	bool anyKey;

	bool p1Fire;
	bool p2Fire;

	bool isServer = true;
	bool quitting = false;
	RemotePlayer * remotePlayer;
	void sendGrid();
	void startGame();

	void giveRenderer(SDL_Renderer* ren);

	int registerPhys(PhysObj * obj);
	int registerRender(RenderObject * obj);
	void runUpdate(double simLength);
	void render(SDL_Renderer* ren);

	void cleanup();

	//void turnover(int winner);

	void loadScene(SceneList scene);
	

private:
	Scene()
	{
		std::cout << "Init Scene" << std::endl;
		sound = new Sound();
		textures = new TextureManager();
		remotePlayer = new RemotePlayerAI();
	};

	void changeScene();

	static Scene* _theScene;
	SDL_Renderer* renderer;
};


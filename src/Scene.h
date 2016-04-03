#pragma once
#include <vector>
#include <map>
#include <string>
#include <iostream>

#include "PhysObj.h"
#include "RenderObject.h"
#include "Sound.h"

struct WorldBounds
{
	float minX;
	float minY;
	float maxX;
	float maxY;
};

struct MouseData
{
	float mouseX;
	float mouseY;
	bool leftMouse;
	bool rightMouse;
	bool leftMouseOnce;
	bool rightMouseOnce;
};

enum SceneList
{
	SCENE_MENU, SCENE_TITLE, SCENE_INSTRUCTIONS, SCENE_PREGAME,
	SCENE_GAME_OURTURN, SCENE_GAME_THEIRTURN,
	SCENE_TEST_SCENE
};

class Scene
{
public:
	static Scene& getScene();
	std::vector<PhysObj *> PhysList;
	std::vector<RenderObject *> RenderList;
	std::map<std::string, std::string> SceneData;
	
	WorldBounds bounds = { 0, 0, 600, 600 };
	
	int gridWidth = 60;
	int gridHeight = 60;
	int gridOffsetX = 0;
	int gridOffsetY = 0;

	MouseData mouseData = { 0, 0, false, false };
	void updateMouseData(float x, float y, bool left, bool right);

	Sound* sound;

	SceneList newScene;
	SceneList currentScene;

	float P1_axis_X = 0.0f;
	float p1_axis_Y = 0.0f;
	float p2_axis_X = 0.0f;
	float p2_axis_Y = 0.0f;

	bool anyKey;

	void giveRenderer(SDL_Renderer* ren);

	int registerPhys(PhysObj * obj);
	int registerRender(RenderObject * obj);
	void runUpdate(double simLength);
	void render(SDL_Renderer* ren);

	void cleanup();

	void loadScene(SceneList scene);

private:
	Scene()
	{
		std::cout << "Init Scene" << std::endl;
		sound = new Sound();

	};

	void changeScene();

	static Scene* _theScene;
	SDL_Renderer* renderer;
};


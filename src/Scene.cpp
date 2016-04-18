#include "Scene.h"

#include <iostream>
#include <string>

#include "TestScreen.h"
#include "PregameScreen.h"
#include "GameGrid.h"

Scene* Scene::_theScene;

Scene& Scene::getScene() 
{
	if (_theScene == NULL) _theScene = new Scene();
	return *_theScene;
}

// Intended to be called once per frame from the main loop by the input handling.
// Responsible for updating mouse state and setting/unsetting the single press inputs.
void Scene::updateMouseData(float x, float y, bool left, bool right)
{
	mouseData.leftMouseOnce = false;
	mouseData.rightMouseOnce = false;

	mouseData.mouseX = x;
	mouseData.mouseY = y;
	if (mouseData.leftMouse != left)
	{
		mouseData.leftMouse = left;
		if (left)
		{
			mouseData.leftMouseOnce = true;
		}
	}
	if (mouseData.rightMouse != right)
	{
		mouseData.rightMouse = right;
		if (right)
		{
			mouseData.rightMouseOnce = true;
		}
	}
}

// Store Renderer pointer for Scene Changes. TODO: Possibly no more need for passing this all the time?
void Scene::giveRenderer(SDL_Renderer * ren)
{
	this->renderer = ren;
}

// Add an object to the Phys list
int Scene::registerPhys(PhysObj * obj)
{
	PhysList.push_back(obj);
	std::cout << "Registered Phys Object: " << &obj << std::endl;
	return 0;
}

// Add an object to the Render List
int Scene::registerRender(RenderObject * obj)
{
	RenderList.push_back(obj);
	std::cout << "Registered Render Object: " << obj << " ID: " << obj->id << std::endl;
	return 0;
}

// Run an update Cycle (and change scene if requested)
void Scene::runUpdate(double simLength)
{
	if (!PhysList.empty())
	{
		for (auto const& object : PhysList)
		{
			object->preStep();
		}
		for (auto const& object : PhysList)
		{
			object->tickPhysics(simLength);
		}
		for (auto const& object : PhysList)
		{
			object->postStep();
		}
	}
	if (!RenderList.empty())
	{
		for (auto const& object : RenderList)
		{
			object->update(simLength);
		}
	}

	if (newScene != currentScene)
	{
		changeScene();
	}
}

// Run a render cycle
void Scene::render(SDL_Renderer* ren)
{
	if (!RenderList.empty())
	{
		for (auto const& object : RenderList)
		{
			object->render(ren);
		}
	}
}

// Delete all objects in prep for a new scene
void Scene::cleanup()
{
	for (auto obj : PhysList)
	{
		delete obj;
	}
	PhysList.clear();
	for (auto obj : RenderList)
	{
		delete obj;
	}
	RenderList.clear();
}

void loadTestScreen(SDL_Renderer* ren)
{
	TestScreen* screen = new TestScreen(ren, "_TestScreen");
	Scene::getScene().registerRender(screen);
}

void loadMainMenu(SDL_Renderer* ren)
{
	GUIButton* button1 = new GUIButton(ren, "Start Game", 100, 100, []() {Scene::getScene().loadScene(SCENE_TEST_SCENE); }, "_MainMenu_Button1");
	GUIButton* button2 = new GUIButton(ren, "Instructions", 100, 200, []() {Scene::getScene().loadScene(SCENE_INSTRUCTIONS); }, "_MainMenu_Button2");
	GUIButton* button3 = new GUIButton(ren, "Quit", 100, 300, []() {Scene::getScene().loadScene(SCENE_TEST_SCENE); }, "_MainMenu_Button3");

	Scene::getScene().registerRender(button1);
	Scene::getScene().registerRender(button2);
	Scene::getScene().registerRender(button3);
}

void loadInstructions(SDL_Renderer* ren)
{
	GUIButton* button = new GUIButton(ren, "Back", 300, 300, []() {Scene::getScene().loadScene(SCENE_MENU); }, "_instructions_BackButton");
	Scene::getScene().registerRender(button);

	TextSprite* text = new TextSprite("./assets/Hack-Regular.ttf", 64, "Instructions go here. \ninstructions go here!", ren, "_instructions_text");
	text->setScale(0.25f);
	text->moveString(100, 100);
	Scene::getScene().registerRender(text);
	
}

void loadPregame(SDL_Renderer* ren)
{
	PregameScreen* screen = new PregameScreen(ren, "_pregameScreen");
	Scene::getScene().registerRender(screen);
}

void makeP2()
{
	/*
	 TODO: THIS
	 TODO: RemotePlayer class
	 TODO: RemotePlayerAI class
	 TODO: RemotePlayerLocal class
	 TODO: RemotePlayerNetwork class?
	if (multiplayer)
		Let P2 place ships
	else
		init AI
		Generate Grid
	
	*/
}

void loadTheirGrid(SDL_Renderer* ren)
{
	if (Scene::getScene().p2Data.ships[0].size = 0)
	{
		makeP2();
	}
	GameGrid* grid = new GameGrid(THEIR_GRID, ren, "_ThierGrid");

	Scene::getScene().registerRender(grid);

}

void loadOurGrid(SDL_Renderer* ren)
{
	GameGrid* grid = new GameGrid(OUR_GRID, ren, "_OurGrid");

	Scene::getScene().registerRender(grid);
}

void Scene::turnover(int winner)
{
	switch (winner)
	{
	case 0:
		if (turn == 1)
		{
			turn = 2;
			loadScene(SCENE_GAME_THEIRGRID);
		}
		else {
			turn = 1;
			loadScene(SCENE_GAME_OURGRID);
		}
		break;
	case 1:
		//Local player won
		break;
	case 2:
		//Remote/AI player won
		break;
	default:
		break;
	}
}

// Request a Scene change
void Scene::loadScene(SceneList scene)
{
	newScene = scene;
}

// Acutally do the scene change.
void Scene::changeScene()
{
	switch (newScene)
	{
	case SCENE_TITLE:
		cleanup();
		break;
	case SCENE_MENU:
		cleanup();
		loadMainMenu(renderer);
		break;
	case SCENE_INSTRUCTIONS:
		cleanup();
		loadInstructions(renderer);
		break;
	case SCENE_PREGAME:
		cleanup();
		loadPregame(renderer);
		break;
	case SCENE_TEST_SCENE:
		cleanup();
		loadTestScreen(renderer);
		break;
	case SCENE_GAME_OURGRID:
		cleanup();
		loadOurGrid(renderer);
		break;
	case SCENE_GAME_THEIRGRID:
		cleanup();
		loadTheirGrid(renderer);
	default:
		break;
	}
	currentScene = newScene;
}

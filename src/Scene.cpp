#include "Scene.h"

#include <iostream>
#include <string>

#include "TestScreen.h"
#include "PregameScreen.h"

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

void Scene::giveRenderer(SDL_Renderer * ren)
{
	this->renderer = ren;
}

int Scene::registerPhys(PhysObj * obj)
{
	PhysList.push_back(obj);
	std::cout << "Registered Phys Object: " << &obj << std::endl;
	return 0;
}

int Scene::registerRender(RenderObject * obj)
{
	RenderList.push_back(obj);
	std::cout << "Registered Render Object: " << obj << " ID: " << obj->id << std::endl;
	return 0;
}

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

void Scene::loadScene(SceneList scene)
{
	newScene = scene;
}

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
	default:
		break;
	}
	currentScene = newScene;
}

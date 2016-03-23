#include "Scene.h"

#include <iostream>
#include <string>

enum SceneList
{
	SCENE_MENU, SCENE_TITLE, SCENE_PREGAME,
	SCENE_GAME_OURTURN, SCENE_GAME_THEIRTURN
};

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

int Scene::registerPhys(PhysObj * obj)
{
	PhysList.push_back(obj);
	std::cout << "Registered Phys Object: " << &obj << std::endl;
	return 0;
}

int Scene::registerRender(RenderObject * obj)
{
	RenderList.push_back(obj);
	std::cout << "Registered Render Object: " << &obj << std::endl;
	return 0;
}

void Scene::runUpdate(double simLength)
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
	for (auto const& object : RenderList)
	{
		object->update(simLength);
	}
}

void Scene::render(SDL_Renderer* ren)
{
	for (auto const& object : RenderList)
	{
		object->render(ren);
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

void Scene::loadScene(SceneList scene)
{
	switch (scene)
	{
	case SCENE_TITLE:
		cleanup();
		break;
	case SCENE_MENU:
		cleanup();
		break;
	case SCENE_PREGAME:
		cleanup();
		break;
	default:
		break;
	}
}
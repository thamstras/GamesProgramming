#include "Scene.h"

#include <iostream>
#include <string>

Scene* Scene::_theScene;

Scene& Scene::getScene() 
{
	if (_theScene == NULL) _theScene = new Scene();
	return *_theScene;
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
		object->tickPhysics(simLength);
	}
	for (auto const& object : PhysList)
	{
		object->updatePhysics();
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

#include "Scene.h"

Scene::Scene()
{
}

Scene::~Scene()
{
}

int Scene::registerPhys(PhysObj * obj)
{
	return 0;
}

int Scene::registerRender(RenderObject * obj)
{
	return 0;
}

void Scene::runUpdate(double simLength)
{
	for (auto const& object : PhysList)
	{
		object->updatePhysics();
	}
	for (auto const& object : RenderList)
	{
		object->update(simLength);
	}
}

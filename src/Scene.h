#pragma once
#include <vector>
#include "PhysObj.h"
#include "RenderObject.h"

class Scene
{
public:
	static std::vector<PhysObj*> PhysList;
	static std::vector<RenderObject*> RenderList;
	Scene();
	~Scene();

private:

};

Scene::Scene()
{
}

Scene::~Scene()
{
}
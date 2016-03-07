#pragma once
#include <vector>
#include <map>
#include <string>
#include <iostream>

#include "PhysObj.h"
#include "RenderObject.h"

class Scene
{
public:
	static Scene& getScene();
	std::vector<PhysObj *> PhysList;
	std::vector<RenderObject *> RenderList;
	std::map<std::string, std::string> SceneData;
	
	int registerPhys(PhysObj * obj);
	int registerRender(RenderObject * obj);
	void runUpdate(double simLength);
	void render(SDL_Renderer* ren);

	void cleanup();

private:
	Scene() { std::cout << "Init Scene" << std::endl; };

	static Scene* _theScene;
};


#pragma once
#include <vector>
#include <map>
#include <string>

#include "PhysObj.h"
#include "RenderObject.h"

class Scene
{
public:
	static Scene& getScene() { return _theScene; };
	std::vector<PhysObj *> PhysList;
	std::vector<RenderObject *> RenderList;
	std::map<std::string, std::string> SceneData;
	Scene();
	~Scene();
	int registerPhys(PhysObj * obj);
	int registerRender(RenderObject * obj);
	void runUpdate(double simLength);

private:
	static Scene _theScene;
};


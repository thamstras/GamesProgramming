#pragma once
#include <vector>
#include <iostream>
#include "Scene.h"
#include "PhysObj.h"

class DronePhys : public PhysObj
{
public:
	DronePhys();
	~DronePhys();
	void tickPhysics(double simLength);
	void updatePhysics();
	double radius;
private:

};
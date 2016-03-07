#pragma once
#include <vector>
#include <iostream>
#include "PhysObj.h"
#include "Scene.h"

class DronePhys : public PhysObj
{
public:
	DronePhys();
	DronePhys(const DronePhys& other);
	~DronePhys();
	void tickPhysics(double simLength);
	void updatePhysics();
	double radius;
	double mass;
private:

};
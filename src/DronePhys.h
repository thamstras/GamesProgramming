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
	void preStep();
	void tickPhysics(double simLength);
	void postStep();

	double radius = 1.0f;
	double mass = 1.0f;
	bool collided = false;
	int playerBind = 0;

	float inputAxisX = 0.0f;
	float inputAxisY = 0.0f;

	glm::dvec2 forceAcc = glm::dvec2(0.0f);

	double inputForceTweak = 100.0f; //tODO make bibgger?
	double airResist = 0.1f;
private:

};
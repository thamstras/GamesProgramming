#pragma once

#include <glm/glm.hpp>

#include "Scene.h"

class PhysObj
{
public:
	PhysObj();
	virtual ~PhysObj();
	virtual void tickPhysics();
	virtual void updatePhysics();

protected:
	glm::dvec2 _position;
	glm::dvec2 _velocity;
	
	glm::dvec2 _newPosition;
	glm::dvec2 _newVelocity;
	
	bool gravityOn;
	glm::dvec2 _gravity = glm::dvec2(0.0f, -9.81f);

};
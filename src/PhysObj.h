#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>

class PhysObj
{
public:
	PhysObj();
	virtual ~PhysObj();
	virtual void preStep() = 0;
	virtual void tickPhysics(double simLength) = 0;
	virtual void postStep() = 0;
	glm::dvec2 _position;
	glm::dvec2 _velocity;

protected:
	glm::dvec2 _newPosition;
	glm::dvec2 _newVelocity;
	
	bool gravityOn;
	glm::dvec2 _gravity = glm::dvec2(0.0f, -9.81f);

};
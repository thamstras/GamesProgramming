#pragma once

#include <glm/glm.hpp>

#include "Scene.h"

/*
struct Ball {
vec2 center;
float radius;
};

struct Box {
vec2 center;
float xSize; // half width
float ySize; // half height
};

//Circle-Circle collision
Ball ball1;
Ball ball2;

float distX = ball1.position.x - ball2.position.x;
float distY = ball1.position.y - ball2.position.y;
float distance = Math.sqrt(distX*distX + distY*distY);
bool colliding = (distance <= ball1.radius + ball2.radius);


//Box-Box collision
Box box1;
Box box2;
bool xCollision = box1.position.x + box1.xSize < box2.position.x - box2.xSize || box1.position.x - box1.xSize > box2.position.x + box2.position.xSize;
bool yCollision = box1.position.y + box1.ySize < box2.position.y - box2.ySize || box1.position.y - box1.xSize > box2.position.y + box2.position.ySize;
bool colliding = xCollision && yCollision;
*/

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
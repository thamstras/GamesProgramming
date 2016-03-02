#pragma once
#include <glm/glm.hpp>

#include "RenderObject.h"
#include "StaticSprite.h"
#include "PhysObj.h"
#include "DronePhys.h"
#include "SDL.h"
class Ball : public RenderObject
{
public:
	Ball(SDL_Renderer* ren);
	~Ball();
	void update(double simLength);
	void render(SDL_Renderer* ren);
private:
	glm::dvec2 _position;
	glm::dvec2 _velocity;
	DronePhys* phys;
	StaticSprite* sprite;
};
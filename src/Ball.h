#pragma once
#include <glm/glm.hpp>

#include "RenderObject.h"
#include "StaticSprite.h"
#include "PhysObj.h"
#include "DronePhys.h"
#include "SDL.h"
#include "Scene.h"

class Ball : public RenderObject
{
public:
	Ball(SDL_Renderer* ren, glm::vec2 pos, glm::vec2 vel, double mass, std::string id);
	~Ball();
	void update(double simLength);
	void render(SDL_Renderer* ren);
	void bindPlayer(int p);
	DronePhys* phys;
	StaticSprite* sprite;
	void enable();
	void disable();
private:
	bool enabled;
	glm::dvec2 _position;
	glm::dvec2 _velocity;
	
};
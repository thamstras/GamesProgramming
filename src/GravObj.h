#pragma once
#include <string>

#include "RenderObject.h"
#include "StaticSprite.h"
#include "glm\glm.hpp"

class GravObj : public RenderObject
{
public:
	GravObj(std::string path, SDL_Renderer* ren, double mass, glm::dvec2 pos);
	~GravObj();

	void update(double simLength);
	void render(SDL_Renderer* ren);

	void setGrav(glm::dvec2 gravSrc, double gravMass);
	void setSrcRect(SDL_Rect rect);

private:
	StaticSprite* sprite;
	glm::dvec2 position;
	glm::dvec2 velocity;
	double mass;
	glm::dvec2 gravSrc;
	double gravMass;
};
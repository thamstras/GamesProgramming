#pragma once
#include <glm/glm.hpp>

#include "StaticSprite.h"
class Ball
{
public:
	Ball();
	~Ball();
private:
	glm::dvec2 _position;
	glm::dvec2 _velocity;
};
#include "Ball.h"

Ball::Ball(SDL_Renderer* ren)
{
	phys = new DronePhys();
	sprite = new StaticSprite("assets\ball.png", ren);
}

Ball::~Ball()
{
}

void Ball::update(double simLength)
{
	_position = phys->_position;
	_velocity = phys->_velocity;
	sprite->moveSprite((int)_position.x, (int)_position.y);
}

void Ball::render(SDL_Renderer * ren)
{
	sprite->render(ren);
}

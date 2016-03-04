#include "Ball.h"

Ball::Ball(SDL_Renderer* ren)
{
	phys = new DronePhys();
	sprite = new StaticSprite("./assets/ball.png", ren);
	phys->mass = 1.0f;
	phys->radius = 32.0f;
	this->_position = glm::vec2(150, 150);
	this->_velocity = glm::vec2(10, 10);
	Scene::getScene().registerPhys(phys);
	Scene::getScene().registerRender(this);
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

#include "Ball.h"

#include <iostream>

Ball::Ball(SDL_Renderer* ren, glm::vec2 pos, glm::vec2 vel)
{
	std::cout << "Ball::Ball(SDL_Renderer* ren) Called" << std::endl;

	phys = new DronePhys();
	sprite = new StaticSprite("./assets/ball.png", ren);
	phys->mass = 1.0f;
	phys->radius = 32.0f;
	phys->_position = pos;
	phys->_velocity = vel;
	this->_position = pos;
	this->_velocity = vel;
	Scene::getScene().registerPhys(phys);
	//Scene::getScene().registerRender(this);
}

Ball::~Ball()
{
	std::cout << "Ball::~Ball() Called " << std::endl << "THIS IS BAD!" << std::endl;
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

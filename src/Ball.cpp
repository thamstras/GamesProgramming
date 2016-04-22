#include "Ball.h"

#include <iostream>

Ball::Ball(SDL_Renderer* ren, glm::vec2 pos, glm::vec2 vel, double mass, std::string id)
{
	std::cout << "Ball::Ball(SDL_Renderer* ren) Called" << std::endl;
	this->id = id;
	phys = new DronePhys();
	sprite = new StaticSprite("ball", ren, this->id + "_sprite");
	phys->mass = 1.0f;
	phys->radius = 32.0f;
	phys->_position = pos;
	phys->_velocity = vel;
	this->_position = pos;
	this->_velocity = vel;
	Scene::getScene().registerPhys(phys);
}

Ball::~Ball()
{
	std::cout << "Destroying " << id << std::endl;
	delete sprite;
}

void Ball::update(double simLength)
{
	_position = phys->_position;
	_velocity = phys->_velocity;
	auto radius = phys->radius;
	sprite->moveSprite((int)(_position.x-radius), (int)(_position.y-radius));
	if (phys->collided)
	{
		Scene::getScene().sound->playSound("explosion");
	}
}

void Ball::render(SDL_Renderer * ren)
{
	sprite->render(ren);
}

void Ball::bindPlayer(int p)
{
	switch (p)
	{
	case 1:
		phys->playerBind = 1;
		break;
	case 2:
		phys->playerBind = 2;
		break;
	default:
		phys->playerBind = 0;
		break;
	}
}

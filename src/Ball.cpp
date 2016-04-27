#include "Ball.h"

#include <iostream>

Ball::Ball(SDL_Renderer* ren, glm::vec2 pos, glm::vec2 vel, double mass, std::string id) : RenderObject(id)
{
	std::cout << "Ball::Ball(SDL_Renderer* ren) Called" << std::endl;
	phys = new DronePhys();
	sprite = new StaticSprite("ball", ren, this->id + "_sprite");
	phys->mass = 1.0f;
	phys->radius = 32.0f;
	phys->_position = pos;
	phys->_velocity = vel;
	this->_position = pos;
	this->_velocity = vel;
	auto radius = phys->radius;
	sprite->moveSprite((int)(_position.x - radius), (int)(_position.y - radius));
	enabled = true;
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

void Ball::enable()
{
	//this->enabled = true;
	//this->phys->enabled = true;
}

void Ball::disable()
{
	//this->enabled = false;
	//this->phys->enabled = false;
}

void Ball::move(int x, int y)
{
	_position.x = x;
	_position.y = y;
	phys->_position.x = x;
	phys->_position.y = y;
	phys->_velocity.x = 0;
	phys->_velocity.y = 0;
	auto radius = phys->radius;
	sprite->moveSprite((int)(_position.x - radius), (int)(_position.y - radius));
}

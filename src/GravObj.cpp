#include "GravObj.h"

GravObj::GravObj(std::string path, SDL_Renderer * ren, double mass, glm::dvec2 pos)
{
	sprite = new StaticSprite(path, ren);
	this->position = pos;
	this->mass = mass;
}

GravObj::~GravObj()
{
	std::cout << "GravObj::~GravObj called. THIS IS BAD!!!";
	delete sprite;
}

void GravObj::update(double simLength)
{
	//std::cout << "GravObj::update called. Obj at: " << position.x << " " << position.y << "\n";
	glm::dvec2 force = glm::vec2(0);

	glm::dvec2 gravForce = gravSrc - position;
	//double gravForceMag = mass*gravMass / (gravForce.length()*gravForce.length());
	double gravForceMag = 1;
	force += gravForce * gravForceMag;

	glm::dvec2 accel = force / mass;
	velocity += accel * simLength;
	position += velocity * simLength;
	sprite->moveSprite(position.x, position.y);
}

void GravObj::render(SDL_Renderer * ren)
{
	//std::cout << "GravObj::render called!\n";
	sprite->render(ren);
}

void GravObj::setGrav(glm::dvec2 gravSrc, double gravMass)
{
	this->gravSrc = gravSrc;
	this->gravMass = gravMass;
}

void GravObj::setSrcRect(SDL_Rect rect)
{
	sprite->setSrcRect(rect);
}

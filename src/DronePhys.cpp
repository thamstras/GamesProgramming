#include "DronePhys.h"

#include <iostream>

DronePhys::DronePhys()
{
	std::cout << "DronePhys::DronePhys() Called" << std::endl;
}

DronePhys::DronePhys(const DronePhys & other)
{
	std::cout << "DronePhys::DronePhys(const DronePhys & other) Called" << std::endl << "THIS IS PROBABLY BAD" << std::endl;
}

DronePhys::~DronePhys()
{
	std::cout << "Destroying " << "a DronePhys instance" << std::endl;
}

void DronePhys::preStep()
{
	collided = false;

	_newPosition = _position;
	_newVelocity = _velocity;

	forceAcc = glm::dvec2(0.0f, 0.0f);

	inputAxisX = 0.0f;
	inputAxisX = 0.0f;
	if (playerBind == 1)
	{
		inputAxisX = Scene::getScene().P1_axis_X;
		inputAxisY = Scene::getScene().p1_axis_Y;
	}
	else if (playerBind == 2)
	{
		inputAxisX = Scene::getScene().p2_axis_X;
		inputAxisY = Scene::getScene().p2_axis_Y;
	}
}

void DronePhys::tickPhysics(double simLength)
{
	if (simLength > 0.5f || simLength < 0.000001f)
	{
		return;
	}

	std::vector<PhysObj *> physList = Scene::getScene().PhysList;
	for (auto const& other : physList)
	{
		if (other == this)
			continue;
		if (other->enabled == false)
			continue;
		DronePhys* otherDrone = dynamic_cast<DronePhys*>(other);
		if (otherDrone != 0)
		{
			//collision detect
			double xDiff = this->_position.x - otherDrone->_position.x;
			double yDiff = this->_position.y - otherDrone->_position.y;
			double distance = (xDiff*xDiff) + (yDiff*yDiff);
			double minDist = this->radius + otherDrone->radius;
			bool colliding = distance < minDist*minDist;

			//collision resolve
			if (colliding)
			{
				collided = true;
				
				glm::dvec2 impactVector = glm::normalize(otherDrone->_position - this->_position);	//vector from them to us
				double ourImpactComponent = glm::dot(impactVector, this->_velocity);				//the component of our velocity along the impact vector
				double theirImpactComponent = glm::dot(impactVector, otherDrone->_velocity);		//the component of their velocity along the impact vector
				double newComponent = ((ourImpactComponent * (this->mass - otherDrone->mass)) +  (2* otherDrone->mass * theirImpactComponent)) / (this->mass + otherDrone->mass);
				glm::dvec2 deltaVelocity = (newComponent-ourImpactComponent) * impactVector;
				glm::dvec2 force = (deltaVelocity * mass) / simLength;
				forceAcc += force;
				//this->_newVelocity += deltaVelocity;

			}

		}
		else {
			std::cout << "Unrecognised PhysObj in PhysList";
		}
	}

	WorldBounds bounds = Scene::getScene().bounds;
	if (_position.x - radius <= bounds.minX || _position.x + radius >= bounds.maxX)
	{
		//_newVelocity.x = -1 * _newVelocity.x;
		glm::dvec2 deltaV = glm::dvec2(-2* _velocity.x, 0);
		glm::dvec2 force = (deltaV * mass) / simLength;
		forceAcc += force;
	}
	if (_position.y - radius <= bounds.minY || _position.y + radius >= bounds.maxY)
	{
		//_newVelocity.y = -1 * _newVelocity.y;
		glm::dvec2 deltaV = glm::dvec2(0, -2 * _velocity.y);
		glm::dvec2 force = (deltaV * mass) / simLength;
		forceAcc += force;
	}

	glm::dvec2 inputForce = glm::dvec2(inputAxisX * inputForceTweak, inputAxisY * inputForceTweak);
	forceAcc += inputForce;

	if (inputAxisX == 0.0f && inputAxisY == 0.0f) //If no input, slow down by the square of velocity
	{	
		//glm::dvec2 airResistForce = (_velocity * _velocity) * - airResist; // TODO: use the magnitude squared for the magnitude, and the normalised vector for the direction
		/*glm::dvec2 airResistDirec = glm::normalize(_velocity);
		double airResistMag = glm::length(_velocity) * glm::length(_velocity) * -1 * airResist;
		glm::dvec2 airResistForce = airResistDirec * airResistMag;
		forceAcc += airResistForce;*/
		double fac = 1.0 - (0.8*simLength);
		_velocity = _velocity * fac;
	}

	glm::dvec2 overallAccel = forceAcc / mass;
	glm::dvec2 overallDeltaV = overallAccel * simLength;
	
	_newVelocity = _velocity + overallDeltaV;
	_newPosition = _position + (_newVelocity * simLength);

	//std::cout <<"\r"<< _newVelocity.x << "\t" << _newVelocity.y << "\t" << inputAxisX << "\t" << inputAxisY;
}

void DronePhys::postStep()
{
	_position = _newPosition;
	_velocity = _newVelocity;
}

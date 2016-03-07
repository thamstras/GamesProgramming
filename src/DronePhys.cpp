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
	std::cout << "DronePhys::~DronePhys() Called" << std::endl;
	std::cout << "THIS IS BAD";
}

void DronePhys::tickPhysics(double simLength)
{
	if (simLength > 2.0f || simLength < 0.000001f)
	{
		_newVelocity = _velocity;
		_newPosition = _position;
		return;
	}


	_newVelocity = _velocity;
	_newPosition = _position + _velocity * simLength;
	std::vector<PhysObj *> physList = Scene::getScene().PhysList;
	for (auto const& other : physList)
	{
		if (other == this)
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
				glm::dvec2 impactVector = glm::normalize(otherDrone->_position - this->_position);
				double ourImpactComponent = glm::dot(impactVector, this->_velocity);
				double theirImpactComponent = glm::dot(impactVector, otherDrone->_velocity);
				double newComponent = (ourImpactComponent * (this->mass - otherDrone->mass) + 2 * otherDrone->mass * theirImpactComponent) / (this->mass + otherDrone->mass);
				glm::dvec2 deltaVelocity = (newComponent-ourImpactComponent) * impactVector;
				this->_newVelocity += deltaVelocity;

			}

		}
		else {
			std::cout << "Unrecognised PhysObj in PhysList";
		}
	}
}

void DronePhys::updatePhysics()
{
	_position = _newPosition;
	_velocity = _newVelocity;
}

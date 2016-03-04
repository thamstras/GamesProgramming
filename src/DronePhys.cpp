#include "DronePhys.h"

DronePhys::DronePhys()
{
}

DronePhys::~DronePhys()
{
}

void DronePhys::tickPhysics(double simLength)
{
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

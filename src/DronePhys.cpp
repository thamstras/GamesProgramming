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

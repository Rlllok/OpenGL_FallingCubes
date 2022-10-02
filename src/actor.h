#pragma once

#include "glm/glm.hpp"
#include <bullet/btBulletDynamicsCommon.h>
#include "collisionBody.h"


class Actor
{
protected:
	btVector3 originPosition;
	btQuaternion originOrientation;
	CollisionBody* collision;
	
public:
	virtual void Display() = 0;
	virtual void Tick(float deltaTime) = 0;
	virtual btVector3 GetOriginPosition();
	virtual CollisionBody* GetCollisionBody();
	virtual btVector3 GetCurrentPosition();
	virtual btQuaternion GetCurrentOrientation();
};
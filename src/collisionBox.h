#pragma once

#include "collisionBody.h"
#include <bullet/btBulletDynamicsCommon.h>


class CollisionBox : public CollisionBody
{
private:
	btVector3 Size;

public:
	CollisionBox(btVector3 position, btQuaternion rotation, btVector3 sizeFromOrigin, float mass);
	~CollisionBox();
};


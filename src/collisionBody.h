#pragma once

#include <bullet/btBulletDynamicsCommon.h>


class CollisionBody
{
protected:

	btVector3 originPosition = btVector3(0.0f, 0.0f, 0.0f);
	btQuaternion originOrientation;
	float mass = 0.0f;
	btTransform transformMatrix;
	btBoxShape* collisionShape = nullptr;
	btMotionState* motionState = nullptr;
	btRigidBody* rigidBody = nullptr;

public:
	
	virtual btVector3 GetOriginPosition();
	virtual float GetMass();
	virtual void SetMass(float objMass);
	virtual btRigidBody* GetRigidBody();
	virtual btVector3 GetCurrentPosition();
	virtual btQuaternion GetCurrentOrientation();
};


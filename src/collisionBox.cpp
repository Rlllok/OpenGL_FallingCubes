#include "collisionBox.h"


CollisionBox::CollisionBox(btVector3 position, btQuaternion rotation, btVector3 sizeFromOrigin, float objMass)
{
	originPosition = position;
	originOrientation = rotation;
	mass = objMass;
	Size = sizeFromOrigin;

	transformMatrix.setIdentity();
	transformMatrix.setOrigin(originPosition);
	transformMatrix.setRotation(originOrientation);
	collisionShape = new btBoxShape(Size);
	motionState = new btDefaultMotionState(transformMatrix);
	btVector3 inertiaBox(0.0, 0.0, 0.0);
	collisionShape->calculateLocalInertia(mass, inertiaBox);
	btRigidBody::btRigidBodyConstructionInfo infoBox(mass, motionState, collisionShape, inertiaBox);
	rigidBody = new btRigidBody(infoBox);
}


CollisionBox::~CollisionBox()
{
	delete collisionShape;
	delete motionState;
	delete rigidBody;
}

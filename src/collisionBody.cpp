#include "collisionBody.h"


btVector3 CollisionBody::GetOriginPosition()
{
    return originPosition;
}


float CollisionBody::GetMass()
{
    return mass;
}


void CollisionBody::SetMass(float objMass)
{
    mass = objMass;
}


btRigidBody* CollisionBody::GetRigidBody()
{
    return rigidBody;
}


btVector3 CollisionBody::GetCurrentPosition()
{
    return rigidBody->getCenterOfMassPosition();
}


btQuaternion CollisionBody::GetCurrentOrientation()
{
    return rigidBody->getOrientation();
}

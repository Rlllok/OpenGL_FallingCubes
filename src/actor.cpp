#include "actor.h"


btVector3 Actor::GetOriginPosition()
{
    return originPosition;
}


CollisionBody* Actor::GetCollisionBody()
{
    return collision;
}


btVector3 Actor::GetCurrentPosition()
{
    if (collision) {
        return collision->GetCurrentPosition();
    }
    else {
        return originPosition;
    }
}


btQuaternion Actor::GetCurrentOrientation()
{
    if (collision) {
        return collision->GetCurrentOrientation();
    }
    else {
        return originOrientation;
    }
}

#pragma once

#include <bullet/btBulletDynamicsCommon.h>
#include "glm/glm.hpp"
#include <vector>
#include "actor.h"
#include "camera.h"
#include "lightSource.h"


class World
{
private:
    Camera* camera;
    LightSource* lightSource;
    btCollisionConfiguration* collisionConfig;
    btDispatcher* dispatcher;
    btBroadphaseInterface* broadphase;
    btConstraintSolver* solver;
    btDynamicsWorld* physicsWorld;

    std::vector<Actor*> actors;

public:

	World(Camera* camera, LightSource* light);
    ~World();
    void AddActor(Actor* actor);
    void RemoveActor(Actor* actor);
    void Tick(float deltaTime);
    Camera* GetCamera();
    LightSource* GetLightSource();
};


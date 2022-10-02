#include "world.h"
#include "collisionBody.h"
#include "actor.h"
#include <algorithm>
#include "boxActor.h"

#include <iostream>


World::World(Camera* camera, LightSource* light)
{
    this->camera = camera;
    lightSource = light;
    collisionConfig = new btDefaultCollisionConfiguration();
    dispatcher = new btCollisionDispatcher(collisionConfig);
    broadphase = new btDbvtBroadphase();
    solver = new btSequentialImpulseConstraintSolver();
    physicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfig);
    physicsWorld->setGravity(btVector3(0, -10, 0));
}


World::~World()
{
    delete camera;
    delete collisionConfig;
    delete dispatcher;
    delete broadphase;
    delete solver;
    delete physicsWorld;

    for (Actor* actor : actors) {
        delete actor;
    }
}


void World::AddActor(Actor* actor)
{
    actors.push_back(actor);
    
    CollisionBody* collision = actor->GetCollisionBody();
    if (collision) {
        physicsWorld->addRigidBody(collision->GetRigidBody());
    }
}


void World::RemoveActor(Actor* actor)
{
    if (actors.size() == 0) { return; }

    physicsWorld->removeRigidBody(actor->GetCollisionBody()->GetRigidBody());
    auto removeIter = std::remove(actors.begin(), actors.end(), actor);
    actors.erase(removeIter, actors.end());
}


void World::Tick(float deltaTime)
{
    physicsWorld->stepSimulation(btScalar(deltaTime));
    for (Actor* actor : actors) {
        actor->Display();
        actor->Tick(deltaTime);
    }
}


Camera* World::GetCamera()
{
    return camera;
}


LightSource* World::GetLightSource()
{
    return lightSource;
}
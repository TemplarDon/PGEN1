#include "ProjectileBase.h"


ProjectileBase::ProjectileBase() :
projectile_Damage(0),
lifespan(0),
currentLifetime(0)
{
}

ProjectileBase::~ProjectileBase()
{
}

bool ProjectileBase::init()
{
    Sequence::create(
        CCDelayTime::create(lifespan),
        CallFunc::create([&]()
    {
        TimeOut();
    }
        ), 
        NULL
        );

    //InitPhysicBody();

    return true;
}

void ProjectileBase::update(double dt)
{
}

void ProjectileBase::TimeOut()
{
    this->removeFromParent();
}

void ProjectileBase::InitPhysicBody()
{
    auto physicsBody = PhysicsBody::createBox(Size(50.f, 50.f),
        PhysicsMaterial(0.1f, 1.0f, 0.0f));

    physicsBody->setGravityEnable(false);
    physicsBody->setRotationEnable(false);

    this->setPhysicsBody(physicsBody);
}
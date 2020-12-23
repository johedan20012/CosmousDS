#ifndef ENTITY_H
#define ENTITY_H

#include "MathHelper.h"

class Entity{
protected:
    unsigned int mId;

    Rect mHitbox;
    bool mIgnoreCollisions;
public:

    Entity(Rect pHitbox);
    virtual ~Entity();

    unsigned long GetId();
    Rect GetHitbox();

    bool CheckCollision(Entity* pOther);

    virtual void Hit();
protected:

    virtual bool IgnoreCollisions();
};

#endif // ENTITY

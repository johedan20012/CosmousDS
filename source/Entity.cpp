#include "Entity.h"
#include "PhysicsManager.h"

Entity::Entity(Rect pHitbox){
    mHitbox = pHitbox;
    mIgnoreCollisions = false;
    mId = 0;
}

Entity::~Entity(){
    if(mId != 0){
        PhysicsManager::Instance()->RemoveEntity(mId);
    }
}

unsigned long Entity::GetId(){
    return mId;
}

Rect Entity::GetHitbox(){
    return mHitbox;
}

bool Entity::CheckCollision(Entity* pOther){
    if(IgnoreCollisions() || pOther->IgnoreCollisions()) return false;
    return RectRectCollision(mHitbox,pOther->GetHitbox());
}

void Entity::Hit(){
}

bool Entity::IgnoreCollisions() {
	return false;
}

#ifndef PHYSICSMANAGER_H
#define PHYSICSMANAGER_H

#include "Entity.h"
#include <vector>

class PhysicsManager{

public:
    enum class CollisionLayers {
        Friendly = 0,
        FriendlyProjectiles,
        Hostile,
        MaxLayers
    };

    enum class CollisionFlags{
        None = 0x00,
        Friendly = 0x01,
        FriendlyProjectiles = 0x02,
        Hostile = 0x04
    };

private:
    static PhysicsManager* sInstance;

    std::vector <Entity*> mEntities[static_cast<unsigned int>(CollisionLayers::MaxLayers)];
    unsigned int mLayersFlags[static_cast<unsigned int>(CollisionLayers::MaxLayers)];

    unsigned int mLastId;

public:

    static PhysicsManager* Instance();
    static void Release();

    void Update();

    unsigned int AddEntity(Entity* pEntity,CollisionLayers pLayer);
    void RemoveEntity(unsigned int pId);
    void SetCollisionFlags(CollisionLayers pLayer,CollisionFlags pFlags);
private:

    PhysicsManager();
    virtual ~PhysicsManager();

};

inline PhysicsManager::CollisionFlags operator | (PhysicsManager::CollisionFlags a, PhysicsManager::CollisionFlags b) {

	return static_cast<PhysicsManager::CollisionFlags>(static_cast<unsigned int>(a) | static_cast<unsigned int>(b));
}

#endif // PHYSICSMANAGER_H

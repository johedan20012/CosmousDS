#include "PhysicsManager.h"

PhysicsManager* PhysicsManager::sInstance = nullptr;

PhysicsManager* PhysicsManager::Instance(){
    if(sInstance == nullptr){
        sInstance = new PhysicsManager();
    }

    return sInstance;
}

void PhysicsManager::Release(){
    delete sInstance;
    sInstance = nullptr;
}

void PhysicsManager::Update(){
    for(unsigned int i=0; i < static_cast<unsigned int>(CollisionLayers::MaxLayers); i++){
        for(unsigned int j=0; j < static_cast<unsigned int>(CollisionLayers::MaxLayers); j++){
            if(mLayersFlags[i]&(1<<j) && i<= j){
                for (unsigned int k = 0; k < mEntities[i].size(); k++) {
					for (unsigned int l = 0; l < mEntities[j].size(); l++) {
						if (mEntities[i][k]->CheckCollision(mEntities[j][l])) {
							mEntities[i][k]->Hit();
							mEntities[j][l]->Hit();
						}
					}
				}
            }
        }
    }
}

unsigned int PhysicsManager::AddEntity(Entity* pEntity,CollisionLayers pLayer){
    mEntities[static_cast<unsigned int>(pLayer)].push_back(pEntity);

    return mLastId++;
}

void PhysicsManager::RemoveEntity(unsigned int pId){
    bool aux=false;
    for(unsigned int i=0; i < static_cast<unsigned int>(CollisionLayers::MaxLayers) && !aux; i++){
        for(unsigned int j=0; j< mEntities[i].size() && !aux; j++){
            if(mEntities[i][j]->GetId() == pId){
                mEntities[i].erase(mEntities[i].begin()+j);
                aux = true;
            }
        }
    }
}

void PhysicsManager::SetCollisionFlags(CollisionLayers pLayer,CollisionFlags pFlags){
    mLayersFlags[static_cast<unsigned int>(pLayer)] = static_cast<unsigned int>(pFlags);
}

PhysicsManager::PhysicsManager(){
    mLastId = 1;
    for (unsigned int i=0; i < static_cast<unsigned int>(CollisionLayers::MaxLayers); i++){
		mLayersFlags[i] = static_cast<unsigned int>(CollisionFlags::None);
	}
}

PhysicsManager::~PhysicsManager(){
}

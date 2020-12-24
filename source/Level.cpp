#include "Level.h"

Level::Level(Player* pPlayer){
    mPlayer = pPlayer;
    mPhysMgr = PhysicsManager::Instance();
    for(int i=0; i<5; i++){
        mEnemies.push_back(new Enemy(Vector2(20+40*i,20),i+5,Enemy::croncher));
        mEnemies.push_back(new Enemy(Vector2(20+40*i,40),i+10,Enemy::muncher));
        mEnemies.push_back(new Enemy(Vector2(20+40*i,60),i+15,Enemy::destroyer));
        mEnemies.push_back(new Enemy(Vector2(20+40*i,80),i+20,Enemy::spawner));
    }
    Enemy::SetPlayer(mPlayer);
    mState = jugando;
}

Level::~Level(){
    for(unsigned int i=0; i<mEnemies.size(); i++){
        delete mEnemies[i];
        mEnemies[i] = nullptr;
    }
}

void Level::Update(){
    bool nivelTerminado = true;
    mPlayer->Update();
    for(unsigned int i=0; i<mEnemies.size(); i++){
        mEnemies[i]->Update();
        if(!mEnemies[i]->IsDead()) nivelTerminado = false;
    }
    if(nivelTerminado) mState = terminado;
    mPhysMgr->Update();
}

bool Level::Finished(){
    return (mState == terminado);
}


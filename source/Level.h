#ifndef LEVEL_H
#define LEVEL_H

#include "Player.h"
#include "Enemy.h"

class Level{
public:
    enum STATE{jugando,terminado};

private:
    Player* mPlayer;
    std::vector<Enemy*> mEnemies;
    PhysicsManager* mPhysMgr;
    STATE mState;

public:

    Level(Player* pPlayer);
    ~Level();

    void Update();
    bool Finished();
};

#endif // LEVEL_H

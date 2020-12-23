#ifndef ENEMY_H
#define ENEMY_H

#include "MathHelper.h"
#include "PhysicsManager.h"
#include "Player.h"
#include <nds.h>

///Sprites
#include "croncherSprite.h"
#include "muncherSprite.h"
#include "destroyerSprite.h"
#include "spawnerSprite.h"

class Enemy : public Entity{

public:
    enum TIPO {croncher,muncher,destroyer,spawner};
    enum ESTADO {live,dead};

private:
    int mOamId;
    TIPO mTipo;
    ESTADO mEstado;
    u16* mSprPtr;
    int mMovX;

protected:
    static Player* sPlayer;

public:

    Enemy(Vector2 pPos,int pOamId,TIPO pTipo);
    ~Enemy();

    void Update();
    void Hit() override;

    static void SetPlayer(Player* pPlayer);
private:

    bool IgnoreCollisions() override;
};

#endif // ENEMY_h

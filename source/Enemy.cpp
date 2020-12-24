#include "Enemy.h"

Player* Enemy::sPlayer = nullptr;

Enemy::Enemy(Vector2 pPos,int pOamId,TIPO pTipo) : Entity(Rect(pPos,16,16)){
    mMovX = 1;
    mTipo = pTipo;
    mEstado = live;
    mOamId = pOamId;
    mHitbox = Rect(pPos, 16,16);

    mSprPtr = oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_Bmp);

    switch(mTipo){
        case croncher:
            dmaCopy(croncherSpriteBitmap, mSprPtr, croncherSpriteBitmapLen);
            break;
        case muncher:
            dmaCopy(muncherSpriteBitmap, mSprPtr, muncherSpriteBitmapLen);
            break;
        case destroyer:
            dmaCopy(destroyerSpriteBitmap, mSprPtr, destroyerSpriteBitmapLen);
            break;
        case spawner:
            dmaCopy(spawnerSpriteBitmap, mSprPtr, spawnerSpriteBitmapLen);
            break;
    }

    oamSet(&oamMain, mOamId, pPos.x, pPos.y, 0, 1, SpriteSize_16x16, SpriteColorFormat_Bmp,
			mSprPtr, -1, false, false, false, false, false);
    mId = PhysicsManager::Instance()->AddEntity(this,PhysicsManager::CollisionLayers::Hostile);
}

Enemy::~Enemy(){
    ///Liberar el espacio del mOamId y la memoria
    oamClearSprite(&oamMain,mOamId);
    oamFreeGfx(&oamMain,mSprPtr);
    PhysicsManager::Instance()->RemoveEntity(mId);
}

void Enemy::Update(){
    if(mEstado == dead) return;
    switch(mTipo){
        case croncher:
            break;
        case muncher:
            break;
        case destroyer:
            break;
        case spawner:
            break;
    }

    mHitbox.moveBy(mMovX,0);
    if(mHitbox.bottomRightCorner().x > 255){
        mHitbox.moveTLTo(Vector2(255-mHitbox.width(),mHitbox.topLeftCorner().y));
        mMovX = -1;
    }
    if(mHitbox.topLeftCorner().x < 0){
        mHitbox.moveTLTo(Vector2(0,mHitbox.topLeftCorner().y));
        mMovX = 1;
    }
    oamSetXY(&oamMain, mOamId, mHitbox.topLeftCorner().x,mHitbox.topLeftCorner().y);
}

void Enemy::Hit(){
    mEstado = dead;
    oamSetHidden(&oamMain,mOamId,true);
    mIgnoreCollisions = true;
    sPlayer->AddScore(10);
}

bool Enemy::IsDead(){
    return (mEstado == dead);
}

void Enemy::SetPlayer(Player* pPlayer){
    sPlayer = pPlayer;
}

bool Enemy::IgnoreCollisions(){
    return (mEstado == dead);
}

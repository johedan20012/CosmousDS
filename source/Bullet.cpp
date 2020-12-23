#include "Bullet.h"

Bullet::Bullet(int pOamId) : Entity(Rect(VEC2_ZERO,3,5)){
    mReady = true;
    mSprPtr = oamAllocateGfx(&oamMain, SpriteSize_8x8, SpriteColorFormat_Bmp);
    mOamId = pOamId;

    mSprPtr[1] =ARGB16(1,31,0,0);
    mSprPtr[9] =ARGB16(1,31,0,0);

    mSprPtr[16] =ARGB16(1,31,0,0);
    mSprPtr[17] =ARGB16(1,31,0,0);
    mSprPtr[18] =ARGB16(1,31,0,0);

    mSprPtr[24] =ARGB16(1,31,0,0);
    mSprPtr[25] =ARGB16(1,31,0,0);
    mSprPtr[26] =ARGB16(1,31,0,0);

    mSprPtr[33] =ARGB16(1,31,0,0);

    oamSet(&oamMain, mOamId, 0, 0, 0, 1, SpriteSize_8x8, SpriteColorFormat_Bmp,
        mSprPtr, -1, false, false, false, false, false);
    oamSetHidden(&oamMain,mOamId,true);
    mId = PhysicsManager::Instance()->AddEntity(this,PhysicsManager::CollisionLayers::FriendlyProjectiles);
}

Bullet::~Bullet(){
    ///Liberar el espacio del mOamId y la memoria
    oamClearSprite(&oamMain,mOamId);
    oamFreeGfx(&oamMain,mSprPtr);
    PhysicsManager::Instance()->RemoveEntity(mId);
}

void Bullet::Hit(){
    mReady = true;
    mIgnoreCollisions = true;
    oamSetHidden(&oamMain,mOamId,true);
}

void Bullet::Fire(Vector2 pPos){
    oamSetHidden(&oamMain,mOamId,false);
    mHitbox.moveTLTo(pPos);
    oamSetXY(&oamMain,mOamId,mHitbox.topLeftCorner().x,mHitbox.topLeftCorner().y);
    mReady = false;
    mIgnoreCollisions = false;
}

void Bullet::Update(){
    if(!mReady){
        mHitbox.moveBy(0,-5);
        if(mHitbox.bottomRightCorner().y < 0){
            mReady = true;
            oamSetHidden(&oamMain,mOamId,true);
            mIgnoreCollisions = true;
        }
        oamSetXY(&oamMain,mOamId,mHitbox.topLeftCorner().x,mHitbox.topLeftCorner().y);
    }
}

bool Bullet::IsReady(){
    return mReady;
}

bool Bullet::IgnoreCollisions(){
    return mReady;
}

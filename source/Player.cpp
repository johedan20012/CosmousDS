#include "Player.h"

Player::Player(int pOamId) : Entity(Rect(Vector2(120,126),16,16)){
    mLifes = 3;
    mScore = 0;

    for(int i=0; i<2; i++){
        mBullets[i] = new Bullet(mOamId+i+1);
    }

    mSprPtr = oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_Bmp);
    mOamId = pOamId;

    dmaCopy(playerSpriteBitmap, mSprPtr, playerSpriteBitmapLen);

    oamSet(&oamMain, mOamId, 120, 126, 0, 1, SpriteSize_16x16, SpriteColorFormat_Bmp,
			mSprPtr, -1, false, false, false, false, false);

    mId = PhysicsManager::Instance()->AddEntity(this,PhysicsManager::CollisionLayers::Friendly);

    mSoundMgr = SoundManager::Instance();
    mmLoadEffect(SFX_LASER);
}

Player::~Player(){
    ///Liberar el espacio del mOamId y la memoria
    oamClearSprite(&oamMain,mOamId);
    oamFreeGfx(&oamMain,mSprPtr);
    PhysicsManager::Instance()->RemoveEntity(mId);

    for(int i=0; i<2; i++){
        delete mBullets[i];
        mBullets[i] = nullptr;
    }
    mmUnloadEffect(SFX_LASER);
}

void Player::Update(){
    if(keysCurrent() & KEY_DOWN){
        if(mHitbox.bottomRightCorner().y < 191) mHitbox.moveBy(0,1);
    }
    if(keysCurrent() & KEY_LEFT){
        if(mHitbox.topLeftCorner().x > 0) mHitbox.moveBy(-1,0);
    }
    if(keysCurrent() & KEY_UP){
        if(mHitbox.topLeftCorner().y > 0) mHitbox.moveBy(0,-1);
    }
    if(keysCurrent() & KEY_RIGHT){
        if(mHitbox.bottomRightCorner().x < 255) mHitbox.moveBy(1,0);
    }
    if(keysDown() & KEY_A){
        for(int i=0; i<2; i++){
            if(mBullets[i]->IsReady()){
                mmEffect(SFX_LASER);
                mBullets[i]->Fire(mHitbox.topLeftCorner()+Vector2(8,0));
                break;
            }
        }
    }

     for(int i=0; i<2; i++){
        mBullets[i]->Update();
    }
    oamSetXY(&oamMain, mOamId, mHitbox.topLeftCorner().x,mHitbox.topLeftCorner().y);
}

void Player::Hit(){
    mLifes --;
    if(mLifes == 0){
        ///TODO GAME OVER
        mLifes = 1;
    }
}

void Player::AddScore(int pScore){
    mScore += pScore;
}

int Player::GetScore(){
    return mScore;
}

int Player::GetLifes(){
    return mLifes;
}

bool Player::IgnoreCollisions(){
    return (mLifes == 0);
}

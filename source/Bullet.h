#ifndef BULLET_H
#define BULLET_H

#include "PhysicsManager.h"
#include <nds.h>

class Bullet : public Entity{
private:
    u16* mSprPtr; ///Puntero a la dirección de memoria donde se guarda el bitmap del sprite del jugador
    int mOamId; ///Id del array del OAM

    bool mReady;
public:
    Bullet(int pOamId);
    ~Bullet();

    void Fire(Vector2 pPos);
    void Hit() override;
    void Update();
    bool IsReady();

private:
    bool IgnoreCollisions() override;
};

#endif // BULLET_H

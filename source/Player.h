#ifndef PLAYER_H
#define PLAYER_H
#include "MathHelper.h"
#include "playerSprite.h"
#include "PhysicsManager.h"
#include "SoundManager.h"
#include "Bullet.h"
#include <nds.h>
#include <maxmod9.h>

///Bancos de sonido
#include "soundbank.h"
#include "soundbank_bin.h"

class Player : public Entity{

private:
    int mLifes;
    int mScore;

    u16* mSprPtr; ///Puntero a la dirección de memoria donde se guarda el bitmap del sprite del jugador
    int mOamId; ///Id del array del OAM

    Bullet* mBullets[2];
    SoundManager* mSoundMgr;

    /*u16* mapaTiles;///memVramMap; ///Esto es un puntero a la parte de la memoria de video donde esta el mapa del fondo 1*/
  /*public:  u16* sprPtr;  ///Esto es un puntero a la dirección de memoria donde se guarda la informacion del sprite de la serpiente
                  ///que solo es la cabeza
           int alfa = 0;*/

public:
    Player(int pOamId);
    ~Player();

    void Update();
    void Hit() override;
    void AddScore(int pScore);
    int GetScore();
    int GetLifes();
private:
    bool IgnoreCollisions() override;
};

#endif // SERPIENTE_H

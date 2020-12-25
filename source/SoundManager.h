#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <maxmod9.h>    // Maxmod definitions for ARM9

class SoundManager{

private:
    static SoundManager* sInstance;

public:

    static SoundManager* Instance();
    static void Release();

    void PlayEffect(unsigned int pSFX);
    void LoadEffect(unsigned int pSFX);
    void UnloadEffect(mm_word pSFX);
private:

    SoundManager();
    ~SoundManager();

};

#endif // SOUNDMANAGER_H

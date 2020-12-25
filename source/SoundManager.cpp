#include "SoundManager.h"

SoundManager* SoundManager::sInstance = nullptr;

SoundManager* SoundManager::Instance(){
    if(sInstance == nullptr){
        sInstance = new SoundManager();
    }
    return sInstance;
}

void SoundManager::Release(){
    delete sInstance;
    sInstance = nullptr;
}

void SoundManager::PlayEffect(unsigned int pSFX){
    mmLoadEffect(pSFX);
}

void SoundManager::LoadEffect(unsigned int pSFX){
    mmEffect(pSFX);
}

void SoundManager::UnloadEffect(mm_word pSFX){
    mmUnloadEffect(pSFX);
}

SoundManager::SoundManager(){
}

SoundManager::~SoundManager(){
}


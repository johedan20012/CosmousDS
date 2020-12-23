#ifndef FUNCTIONHELPER_H
#define FUNCTIONHELPER_H
#include <nds.h>

///Pone el CPU ARM9 en modo sleep durante nFrames
inline void esperar(unsigned int nFrames){
    for(unsigned int a=0; a<nFrames; a++){
        swiWaitForVBlank();
    }
}

///Oscurece un color de 16-bit en formato ABGR haciendo un shift de bits por una posicion a la derecha
int oscurecerColor_X2(int color);

#endif // FUNCTIONHELPER_H


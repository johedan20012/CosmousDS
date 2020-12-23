#include "FunctionHelper.h"

///Oscurece un color de 16-bit en formato ABGR haciendo un shift de bits por una posicion a la derecha
int oscurecerColor_X2(int color){
    int regreso = 1 << 15;
    for(int a=0; a<3; a++){
        ///Este es solo un canal de color. Ya shifteado una posicion a la derecha
        /*
            Canal    Valor de "a"           EJEMPLO
             Red          0             Color = 1 01011 01011 01001
             Green        1             a = 1
             Blue         2             canal =   00101 00000
        */
        int canal = (color & (15 << ((5*a)+1)))>>1;
        regreso |= canal; ///Se pone el canal donde corresponde al color de regreso
    }
    return regreso;
}

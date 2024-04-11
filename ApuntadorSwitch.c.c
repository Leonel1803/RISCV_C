#include "ripes_system.h"

//POINTER TO THE SWITCH
volatile unsigned int * sw = SWITCHES_0_BASE; //32 bits

void main(){
    while(1){
        //printf("%i\n", *sw);
        printf("%i\n", (*sw & 0x01)); //Revisa si está prendido o no
    }
}
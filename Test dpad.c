#include "ripes_system.h"

#define SW0 (0x01)
#define SW1 (0x02)
#define SW2 (0x04)
#define SW3 (0x08)

volatile unsigned int * led_base = LED_MATRIX_0_BASE;
volatile unsigned int * switch_base = SWITCHES_0_BASE;
volatile unsigned int * d_pad = D_PAD_0_UP;

void main()
{
    unsigned int mask = 0;
    
    while(1)
    {
        while(*d_pad == 1)
        {
            *(led_base) = 0x0BDBF0;
        }
        *(led_base) = 0x00;
    } 
}
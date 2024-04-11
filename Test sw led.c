#include "ripes_system.h"

#define SW0 (0x01)
#define SW1 (0x02)
#define SW2 (0x04)
#define SW3 (0x08)

volatile unsigned int * led_base = LED_MATRIX_0_BASE;
volatile unsigned int * switch_base = SWITCHES_0_BASE;

void main()
{
    unsigned int mask = 0;
    
    while(1)
    {
        mask = *switch_base & SW3;
        if(mask == SW3)
        {
           *(led_base) = 0x0BDBD0; 
        }
        else
        {
            *(led_base) = 0x00; 
        }
    }
}
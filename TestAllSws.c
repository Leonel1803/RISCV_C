#include "ripes_system.h"

#define SW0 (0x01)
#define SW1 (0x02)
#define SW2 (0x04)
#define SW3 (0x08)
#define SW4 (0x10)
#define SW5 (0x20)
#define SW6 (0x40)
#define SW7 (0x80)

volatile unsigned int * led_base = LED_MATRIX_0_BASE;
volatile unsigned int * switch_base = SWITCHES_0_BASE;

void main()
{
    unsigned int mask = 0;
    
    while(1)
    {
        if(*switch_base & SW0)
            // SW0 is on
            // RGB value is assigned to the led
            *(led_base) = 0x0BDBD0; 
        if(*switch_base & SW1)
            *(led_base) = 0x0B00D0; 
        if(*switch_base & SW2)
            *(led_base) = 0x0FFBD0; 
        if(*switch_base & SW3)
            *(led_base) = 0x0BDBF0; 
        if(*switch_base & SW4)
            *(led_base) = 0x0BDFF0; 
        if(*switch_base & SW5)
            *(led_base) = 0x0FFFFF; 
        if(*switch_base & SW6)
            *(led_base) = 0x0BBBBB; 
        if(*switch_base & SW6)
            *(led_base) = 0x0BDDFF; 
    }
}
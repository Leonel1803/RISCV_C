#include "ripes_system.h"

int abc[26] = {0b1111110, 0b1111111, 0b0111001, 0b0111111, 0b1111001, 0b1111000, 0b1111011, 0b1110010, 0b0000110, 0b0100111, 0b1111010, 0b0110001, 0b0101010, 0b0111110, 0b0111111, 0b1111100, 0b1011110, 0b0111100, 0b1011011, 0b1110001, 0b0110111, 0b0010111, 0b0010101, 0b1110110, 0b1010111, 0b1001101};

/*     3
     * * *
    *     *
  4 *     * 2
    *  6  *
     * * *
    *     *
  5 *     * 1
    *  0  *
     * * *
*/

volatile unsigned int * led_base = LED_MATRIX_0_BASE;

void printChar(int seg, int x, int y, int color)
{
    led_base += x + LED_MATRIX_0_WIDTH * y;
    int * start = led_base;
    
    if(seg & 0b0000001)
    {
        // Turn on segment 0
        led_base += LED_MATRIX_0_WIDTH * 8 + 1;
        *led_base = color;
        led_base ++;
        *led_base = color;
        led_base ++;
        *led_base = color;
    }
   
    if(seg & 0b0000010)
    {
        // Turn on segment 1
        led_base = start;
        led_base += LED_MATRIX_0_WIDTH * 5 + 4;
        *led_base = color;
        led_base += LED_MATRIX_0_WIDTH;
        *led_base = color;
        led_base += LED_MATRIX_0_WIDTH;
        *led_base = color;
    }
 
    if(seg & 0b0000100)
    {
        // Turn on segment 2
        led_base = start;
        led_base += LED_MATRIX_0_WIDTH + 4;
        *led_base = color;
        led_base += LED_MATRIX_0_WIDTH;
        *led_base = color;
        led_base += LED_MATRIX_0_WIDTH;
        *led_base = color;
    }
 
    if(seg & 0b0001000)
    {
        // Turn on segment 3
        led_base = start;
        led_base += 1;
        *led_base = color;
        led_base ++;
        *led_base = color;
        led_base ++;
        *led_base = color;
    }
    
    if(seg & 0b0010000)
    {
        // Turn on segment 4
        led_base = start;
        led_base += LED_MATRIX_0_WIDTH;
        *led_base = color;
        led_base += LED_MATRIX_0_WIDTH;
        *led_base = color;
        led_base += LED_MATRIX_0_WIDTH;
        *led_base = color;
    }
    
    if(seg & 0b0100000)
    {
        // Turn on segment 5
        led_base = start;
        led_base += LED_MATRIX_0_WIDTH * 5;
        *led_base = color;
        led_base += LED_MATRIX_0_WIDTH;
        *led_base = color;
        led_base += LED_MATRIX_0_WIDTH;
        *led_base = color;
    }
    
    if(seg & 0b1000000)
    {
        // Turn on segment 6
        led_base = start;
        led_base += LED_MATRIX_0_WIDTH *4 + 1;
        *led_base = color;
        led_base ++;
        *led_base = color;
        led_base ++;
        *led_base = color;
    }
    
    led_base = start;
}

void printString(char * str, int lenstr, int x, int y, int color){
    for(int i = 0; i<lenstr; i++){
        int indiceLetra = str[i] - 'a';
        int codigoLetra = abc[indiceLetra];
        printChar(codigoLetra, x+(5+i), y, color);
    }
}

void main()
{
    char str[] = "Hola";
    
     //printChar(abc[24], 35, 5, 0xFFFFFF);
     printString(str, sizeof(str), 0, 0, 0xFFFFFF);
}
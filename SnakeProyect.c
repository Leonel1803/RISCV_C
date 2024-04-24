#include "ripes_system.h"

// Variables y constantes globales
volatile unsigned int *led_base = LED_MATRIX_0_BASE;
volatile unsigned int *d_pad_up = D_PAD_0_UP;
volatile unsigned int *d_pad_do = D_PAD_0_DOWN;
volatile unsigned int *d_pad_le = D_PAD_0_LEFT;
volatile unsigned int *d_pad_ri = D_PAD_0_RIGHT;
int score = 4;
int snakeColor = 0x008000;

void printSnake(volatile unsigned int **line1, volatile unsigned int **line2) {
    // Llenar la primera l?nea de LEDs con el color de la serpiente
    for (int i = 0; i < score; i++) {
        *(*line1)++ = snakeColor;
    }

    // Llenar la segunda l?nea de LEDs con el color de la serpiente
    for (int i = 0; i < score; i++) {
        *(*line2)++ = snakeColor;
    }
    
    printf("%d\n", *line1); // Imprimir direcci?n de line1
    printf("%d\n", *line2); // Imprimir direcci?n de line2
}

void moveSnake(volatile unsigned int **line1, volatile unsigned int **line2) {
    // Mover la serpiente una posici?n hacia la izquierda (por ejemplo)
    // Eliminar la ?ltima posici?n de la serpiente
    *(*line1 - score) = 0x000000;
    *(*line2 - score) = 0x000000;

    // Agregar una nueva parte de la serpiente en la posici?n inicial
    *(*line1)++ = snakeColor;
    *(*line2)++ = snakeColor;
}

int main() {
    // Apuntadores para desplazarse en la matriz de LEDs
    volatile unsigned int *line1 = led_base + 3 + (4 * LED_MATRIX_0_WIDTH);
    volatile unsigned int *line2 = line1 + LED_MATRIX_0_WIDTH; // Desplaza 8 posiciones en memoria
    
    printf("%d\n", line1); // Imprimir direcci?n de line1
    printf("%d\n", line2); // Imprimir direcci?n de line2
    
    printSnake(&line1, &line2);
    
    
    printf("%d\n", line1); // Imprimir direcci?n de line1
    printf("%d\n", line2); // Imprimir direcci?n de line2
    
    while (1) {
        moveSnake(&line1, &line2);
        
        for(int i = 0; i<3000 ; i++);
    }
}
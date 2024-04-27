#include "ripes_system.h"

// Variables y constantes globales
volatile unsigned int *led_base = LED_MATRIX_0_BASE;
volatile unsigned int *d_pad_up = D_PAD_0_UP;
volatile unsigned int *d_pad_do = D_PAD_0_DOWN;
volatile unsigned int *d_pad_le = D_PAD_0_LEFT;
volatile unsigned int *d_pad_ri = D_PAD_0_RIGHT;
int direction = 1;
int pastDirection = 1;
int alive = 1;
//1: Derecha
//2: Abajo
//3: Izquierda
//4: Arriba

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
    switch(direction){
        case 1:
            // Eliminar la ?ltima posici?n de la serpiente
            *(*line1 - score) = 0x000000;
            *(*line2 - score) = 0x000000;

            // Agregar una nueva parte de la serpiente en la posici?n inicial
            *(*line1)++ = snakeColor;
            *(*line2)++ = snakeColor;
            break;
        case 3:
            // Eliminar la ?ltima posici?n de la serpiente
            *(*line1 + score) = 0x000000;
            *(*line2 + score) = 0x000000;

            // Agregar una nueva parte de la serpiente en la posici?n inicial
            *(*line1)-- = snakeColor;
            *(*line2)-- = snakeColor;  
            break;
        case 2:
            if(pastDirection == 1){ //Si antes iba a la derecha
                // Eliminar la ?ltima posici?n de la serpiente
                *(*line1 - score) = 0x000000;
                *(*line2 - score) = 0x000000;
            
                printf("Abajo");
            
                // Mover la serpiente hacia abajo en la misma columna
                *line1 = *line1 + (LED_MATRIX_0_WIDTH * 2);
                *line2 = *line2 + (LED_MATRIX_0_WIDTH - 1);
                
                pastDirection = 2;
            }
            else{
                *(*line1 - (LED_MATRIX_0_WIDTH * score)) = 0x000000;
                *(*line2 - (LED_MATRIX_0_WIDTH * score)) = 0x000000;
                
               *line1 = *line1 + LED_MATRIX_0_WIDTH;
               *line2 = *line2 + LED_MATRIX_0_WIDTH; 
               
               *(*line1) = snakeColor;
               *(*line2) = snakeColor;  
            }
            break;
        case 4:
            if(pastDirection == 1){ //Si antes iba a la derecha
                // Eliminar la ?ltima posici?n de la serpiente
                *(*line1 - score) = 0x000000;
                *(*line2 - score) = 0x000000;
            
                // Mover la serpiente hacia abajo en la misma columna
                *line1 = *line1 + (LED_MATRIX_0_WIDTH * 2);
                *line2 = *line2 + (LED_MATRIX_0_WIDTH - 1);
                
                pastDirection = 2;
            }
            else{
                *(*line1 + (LED_MATRIX_0_WIDTH * score)) = 0x000000;
                *(*line2 + (LED_MATRIX_0_WIDTH * score)) = 0x000000;
                
               *line1 = *line1 - LED_MATRIX_0_WIDTH;
               *line2 = *line2 - LED_MATRIX_0_WIDTH; 
               
               *(*line1) = snakeColor;
               *(*line2) = snakeColor;  
            }
            break;
        default:
            break;
    }
}

int verifyAlive(volatile unsigned int **line1, volatile unsigned int **line2) {
    switch(direction) {
        case 1:
            if ((*line1 - led_base) % LED_MATRIX_0_WIDTH == 0) {
                return 0;
            }
            return 1;
        case 3:
             if ((*line1 - led_base) % LED_MATRIX_0_WIDTH == 0) {
                return 0;
            }
            return 1;
        case 2:
            if (*line1 - led_base >= (LED_MATRIX_0_WIDTH * LED_MATRIX_0_HEIGHT) - LED_MATRIX_0_WIDTH) {
                return 0;
            }
            return 1;
        case 4: 
            if (*line1 - led_base < LED_MATRIX_0_WIDTH) {
                return 0;
            }
            return 1;
        default:
            return 1;
    }
}

void handleDpadInput() {
    if (*d_pad_up == 1) {
        direction = 4; // Arriba
    } else if (*d_pad_do == 1) {
        direction = 2; // Abajo
    } else if (*d_pad_le == 1) {
        direction = 3; // Izquierda
    } else if (*d_pad_ri == 1) {
        direction = 1; // Derecha
    }
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
    
    while (alive) {
        // Gesti?n de las entradas del D-pad
        handleDpadInput();
        
        moveSnake(&line1, &line2);
        
        alive = verifyAlive(&line1, &line2);
        
        for(int i = 0; i<2500 ; i++);
    }
}
#include "ripes_system.h"

// Variables y constantes globales
volatile unsigned int *led_base = LED_MATRIX_0_BASE;
volatile unsigned int * switch_base = SWITCHES_0_BASE;
volatile unsigned int *d_pad_up = D_PAD_0_UP;
volatile unsigned int *d_pad_do = D_PAD_0_DOWN;
volatile unsigned int *d_pad_le = D_PAD_0_LEFT;
volatile unsigned int *d_pad_ri = D_PAD_0_RIGHT;
volatile unsigned int * led_matrix = LED_MATRIX_0_BASE;
#define SW0 (0x01)
int direction = 1;
int pastDirection = 1;
int alive = 1;
//1: Derecha
//2: Abajo
//3: Izquierda
//4: Arriba

int score = 4;
int snakeColor = 0x008000;
int debugColor = 0x0000ff;

void printSnake(volatile unsigned int **line1, volatile unsigned int **line2, volatile unsigned int **line1_tail, volatile unsigned int **line2_tail) {
    // Llenar la primera l?nea de LEDs con el color de la serpiente
    for (int i = 0; i < score; i++) {
        *(*line1)++ = snakeColor;
    }

    // Llenar la segunda l?nea de LEDs con el color de la serpiente
    for (int i = 0; i < score; i++) {
        *(*line2)++ = snakeColor;
    }
    
    *(*line1_tail) = *(*line1) - score;
    *(*line2_tail) = *(*line2) - score;
}

void moveSnake(volatile unsigned int **line1, volatile unsigned int **line2, volatile unsigned int **line1_tail, volatile unsigned int **line2_tail) {
    switch(direction){
        case 1:
            if(pastDirection != direction){
                if(pastDirection == 2){
                    *(*line1_tail) = 0x000000;
                    *(*line2_tail - 1) = 0x000000;
    
                    *line1_tail += LED_MATRIX_0_WIDTH;
                    *line2_tail += LED_MATRIX_0_WIDTH; 
                    
                    if(*(*line1_tail + LED_MATRIX_0_WIDTH + 1) == snakeColor){
                        *line2_tail += LED_MATRIX_0_WIDTH - 1;
                        *line1 -= LED_MATRIX_0_WIDTH;
                        *line1_tail += - 1;
                        pastDirection = 1;
                    }
                    else if(*(*line2_tail + LED_MATRIX_0_WIDTH - 1) == snakeColor){
                        pastDirection = 3;
                    }
                }
                if(pastDirection == 4){
                    *(*line1_tail) = 0x000000;
                    *(*line2_tail + 1) = 0x000000;
    
                    *line1_tail -= LED_MATRIX_0_WIDTH;
                    *line2_tail -= LED_MATRIX_0_WIDTH; 
                    
                    if(*(*line1_tail - LED_MATRIX_0_WIDTH + 1) == snakeColor){
                        pastDirection = 1;
                    }
                    else if(*(*line2_tail + LED_MATRIX_0_WIDTH - 1) == snakeColor){
                        *line2_tail -= LED_MATRIX_0_WIDTH;
                        *line2 -= LED_MATRIX_0_WIDTH;
                        pastDirection = 3;
                    }
                }
                if(pastDirection == 3){
                    *(*line1_tail) = 0x000000;
                    *(*line2_tail) = 0x000000;
            
                    *(*line1_tail)--;
                    *(*line2_tail)--;
                    
                    if(*(*line1_tail - LED_MATRIX_0_WIDTH) == snakeColor){
                        pastDirection = 4;
                    }
                    else if(*(*line2_tail + LED_MATRIX_0_WIDTH) == snakeColor){
                        pastDirection = 2;
                    }
                }
            }
            else{
                *(*line1_tail) = 0x000000;
                *(*line2_tail) = 0x000000;
            
                *(*line1_tail)++;
                *(*line2_tail)++; 
           }
             
            // Agregar una nueva parte de la serpiente en la posici?n inicial
            *(*line1)++ = snakeColor;
            *(*line2)++ = snakeColor;
            break;
        case 3:
            if(pastDirection != direction){
                if(pastDirection == 2){
                    *(*line1_tail) = 0x000000;
                    *(*line2_tail - 1) = 0x000000;
    
                    *line1_tail += LED_MATRIX_0_WIDTH;
                    *line2_tail += LED_MATRIX_0_WIDTH; 
                    
                    if(*(*line1_tail + LED_MATRIX_0_WIDTH + 1) == snakeColor){
                        *(*line1_tail) = 0x000000;
                        *(*line2_tail - 1) = 0x000000;
                        *line2_tail += LED_MATRIX_0_WIDTH - 1;
                        *line1 -= LED_MATRIX_0_WIDTH;
                        *line1_tail += - 1;
                        pastDirection = 1;
                    }
                    else if(*(*line2_tail + LED_MATRIX_0_WIDTH - 1) == snakeColor){
                        *(*line1_tail) = 0x000000;
                        *(*line2_tail - 1) = 0x000000;
                        *line2_tail += LED_MATRIX_0_WIDTH + LED_MATRIX_0_WIDTH + 3;
                        *line1 -= LED_MATRIX_0_WIDTH;
                        *line1_tail += LED_MATRIX_0_WIDTH + 3;
                        pastDirection = 3;
                    }
                }
                if(pastDirection == 4){
                    *(*line1_tail) = 0x000000;
                    *(*line2_tail) = 0x000000 ;
    
                    *line1_tail -= LED_MATRIX_0_WIDTH;
                    *line2_tail -= LED_MATRIX_0_WIDTH; 
                    
                    if(*(*line1_tail - (2 * LED_MATRIX_0_WIDTH)) == snakeColor){
                        *(*line2_tail + 1) = 0x000000;
                        *(*line2_tail + LED_MATRIX_0_WIDTH) = 0x000000;
                        *(*line2_tail + LED_MATRIX_0_WIDTH + 1) = 0x000000;
                        
                        *line2_tail -= 2 * LED_MATRIX_0_WIDTH;
                        *line1_tail -= LED_MATRIX_0_WIDTH;
                        *line2_tail += 3;
                        *line1_tail += 3;
                        *line1 += LED_MATRIX_0_WIDTH;
                        printf("Hola Amigo i");
                        pastDirection = 3;
                    }
                    else if(*(*line1_tail  - (2 * LED_MATRIX_0_WIDTH) + 3) == snakeColor){
                        *line2_tail -= LED_MATRIX_0_WIDTH;
                        *line1 += LED_MATRIX_0_WIDTH;
                        printf("Hola amigo d");
                        pastDirection = 1;
                    }
                }
                if(pastDirection == 1){
                    *(*line1_tail) = 0x000000;
                    *(*line2_tail) = 0x000000;
            
                    *(*line1_tail)--;
                    *(*line2_tail)--;
                    
                    if(*(*line1_tail - LED_MATRIX_0_WIDTH) == snakeColor){
                        pastDirection = 4;
                    }
                    else if(*(*line2_tail + LED_MATRIX_0_WIDTH) == snakeColor){
                        pastDirection = 2;
                    }
                }
            }
            else{
                *(*line1_tail) = 0x000000;
                *(*line2_tail) = 0x000000;
            
                *(*line1_tail)--;
                *(*line2_tail)--;
            }

            // Agregar una nueva parte de la serpiente en la posici?n inicial
            *(*line1)-- = snakeColor;
            *(*line2)-- = snakeColor;  
            break;
        case 2:
            if(pastDirection != direction){
                if(pastDirection == 1){
                    *(*line1_tail) = 0x000000;
                    *(*line2_tail) = 0x000000;
            
                    *(*line1_tail)++;
                    *(*line2_tail)++;
                    
                    if(*(*line1_tail - LED_MATRIX_0_WIDTH) == snakeColor){
                        pastDirection = 4;
                    }
                    else if(*(*line2_tail + LED_MATRIX_0_WIDTH) == snakeColor){
                        *line2_tail -= LED_MATRIX_0_WIDTH - 1;
                        *line2 -= LED_MATRIX_0_WIDTH;
                        *line1_tail += 1;
                        pastDirection = 2;
                    }
                }
                if(pastDirection == 3){
                    *(*line1_tail) = 0x000000;
                    *(*line2_tail) = 0x000000;
            
                    *(*line1_tail)--;
                    *(*line2_tail)--;
                    
                     if(*(*line1_tail - LED_MATRIX_0_WIDTH) == snakeColor){
                        *(*line1) = 0x000000;
                        *(*line2) = 0x000000;
                        *line1 += LED_MATRIX_0_WIDTH;
                        *line2 += LED_MATRIX_0_WIDTH;
                        *line1_tail += LED_MATRIX_0_WIDTH;
                        *line1 += LED_MATRIX_0_WIDTH;
                        pastDirection = 4;
                    }
                    else if(*(*line2_tail + LED_MATRIX_0_WIDTH) == snakeColor){
                        *(*line1) = 0x000000;
                        *(*line2) = 0x000000;
                        *line1 -= LED_MATRIX_0_WIDTH;
                        *line2 -= LED_MATRIX_0_WIDTH;
                        *line2_tail -= LED_MATRIX_0_WIDTH;
                        *line2 -= LED_MATRIX_0_WIDTH;
                        pastDirection = 2;
                    }
                }
                if(pastDirection == 4){
                    *(*line1_tail) = 0x000000;
                    *(*line2_tail + 1) = 0x000000;
    
                    *line1_tail -= LED_MATRIX_0_WIDTH;
                    *line2_tail -= LED_MATRIX_0_WIDTH; 
                    
                    if(*(*line1_tail - 1) == snakeColor){
                        pastDirection = 3;
                    }
                    else if(*(*line2_tail + 1) == snakeColor){
                        pastDirection = 1;
                    }
                }
            }
            else{
                *(*line1_tail) = 0x000000;
                *(*line2_tail - 1) = 0x000000;
    
                *line1_tail += LED_MATRIX_0_WIDTH;
                *line2_tail += LED_MATRIX_0_WIDTH; 
            }
             
            *line1 += LED_MATRIX_0_WIDTH;
            *line2 += LED_MATRIX_0_WIDTH; 
       
            *(*line1) = snakeColor;
            *(*line2 - 1) = snakeColor;  // Cambiado para asignar el color correctamente
            break;
        case 4:
            if(pastDirection != direction){
                if(pastDirection == 1){
                    *(*line1_tail) = 0x000000;
                    *(*line2_tail) = 0x000000;
            
                    *(*line1_tail)++;
                    *(*line2_tail)++;
                    
                    if(*(*line1_tail - LED_MATRIX_0_WIDTH) == snakeColor){
                        *(*line1) = 0x000000;
                        *(*line2) = 0x000000;
                        *line1 += LED_MATRIX_0_WIDTH;
                        *line2 += LED_MATRIX_0_WIDTH;
                        *line1_tail += LED_MATRIX_0_WIDTH;
                        *line1 += LED_MATRIX_0_WIDTH;
                        pastDirection = 4;
                    }
                    else if(*(*line2_tail + LED_MATRIX_0_WIDTH) == snakeColor){
                        *(*line1) = 0x000000;
                        *(*line2) = 0x000000;
                        *line1 -= LED_MATRIX_0_WIDTH;
                        *line2 -= LED_MATRIX_0_WIDTH;
                        *line2_tail -= LED_MATRIX_0_WIDTH;
                        *line2 -= LED_MATRIX_0_WIDTH;
                        pastDirection = 2;
                    }
                }
            }
            else{
                *(*line1_tail) = 0x000000;
                *(*line2_tail + 1) = 0x000000;
    
                *line1_tail -= LED_MATRIX_0_WIDTH;
                *line2_tail -= LED_MATRIX_0_WIDTH; 
            }
            
            *line1 -= LED_MATRIX_0_WIDTH;
            *line2 -= LED_MATRIX_0_WIDTH; 
       
            *(*line1) = snakeColor;
            *(*line2 + 1) = snakeColor;  // Cambiado para asignar el color correctamente
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
             if ((*line1 - led_base + 1) % LED_MATRIX_0_WIDTH == 0) {
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
    if (*d_pad_up == 1 && direction != 2) {
        direction = 4; // Arriba
    } else if (*d_pad_do == 1 && direction != 4) {
        direction = 2; // Abajo
    } else if (*d_pad_le == 1 && direction != 1) {
        direction = 3; // Izquierda
    } else if (*d_pad_ri == 1 && direction != 3) {
        direction = 1; // Derecha
    }
}

void inicializarSerpiente(volatile unsigned int **line1, volatile unsigned int **line2, 
                          volatile unsigned int **line1_tail, volatile unsigned int **line2_tail) {
  for (int i = 0; i < (LED_MATRIX_0_HEIGHT * LED_MATRIX_0_WIDTH); i++) {
        // Recorrer todas las columnas
         *(led_matrix + i) = 0x000000;
    }
      
    *line1 = led_base + 3 + (4 * LED_MATRIX_0_WIDTH);
    *line2 = *line1 + LED_MATRIX_0_WIDTH;
    *line1_tail = led_base + 3 + (4 * LED_MATRIX_0_WIDTH);
    *line2_tail = *line1_tail + LED_MATRIX_0_WIDTH;
    
    printSnake(line1, line2, line1_tail, line2_tail);
}

int main() {
    volatile unsigned int *line1;
    volatile unsigned int *line2;
    volatile unsigned int *line1_tail;
    volatile unsigned int *line2_tail;
    
    crearSerpiente:
        inicializarSerpiente(&line1, &line2, &line1_tail, &line2_tail);
    
    do {
        while (alive) {
            // Gesti?n de las entradas del D-pad
            handleDpadInput();
        
            moveSnake(&line1, &line2, &line1_tail, &line2_tail);
        
            alive = verifyAlive(&line1, &line2);
        
            for(int i = 0; i < 2500; i++);
        }
        
        if (*switch_base & SW0) {
            score = 4;
            direction = 1;
            pastDirection = 1;
            alive = 1;
            goto crearSerpiente;
        }
    } while (!alive);
    
    return 0;
}
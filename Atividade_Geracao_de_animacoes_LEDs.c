#include <stdio.h>
#include "pico/stdlib.h"
#include <hardware/pio.h>
#include "hardware/clocks.h"
#include "pico/bootrom.h"
#include "ws2818b.pio.h"

// Definição do número de LEDs e pino.
#define LED_COUNT 25   
#define LED_PIN 16

// Definição dos pinos das linhas e colunas do teclado
#define LIN_1 8
#define LIN_2 7
#define LIN_3 6
#define LIN_4 5
#define COL_1 4
#define COL_2 3
#define COL_3 2
#define COL_4 1

// Mapeamento do teclado matricial
const char key_map[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

// Padrões para a palavra teste
int T[5][5][3] = {
    {{0, 255, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 255, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 255, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 255, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 255, 0}, {0, 0, 0}, {0, 0, 0}}
};
int E[5][5][3] = {
    {{255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}},
    {{255, 0, 0}, {0, 0, 0},   {0, 0, 0},   {0, 0, 0},   {0, 0, 0}},
    {{255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {0, 0, 0},   {0, 0, 0}},
    {{255, 0, 0}, {0, 0, 0},   {0, 0, 0},   {0, 0, 0},   {0, 0, 0}},
    {{255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}}
};


int S[5][5][3] = {
    {{0, 0, 255}, {0, 0, 255}, {0, 0, 255}, {0, 0, 255}, {0, 0, 255}},
    {{0, 0, 255}, {0, 0, 0},   {0, 0, 0},   {0, 0, 0},   {0, 0, 0}},
    {{0, 0, 255}, {0, 0, 255}, {0, 0, 255}, {0, 0, 255}, {0, 0, 255}},
    {{0, 0, 0}, {0, 0, 0},   {0, 0, 0},   {0, 0, 0},   {0, 0, 255}},
    {{0, 0, 255}, {0, 0, 255}, {0, 0, 255}, {0, 0, 255}, {0, 0, 255}}
};


double um[25] = { 
    0.0, 1.0, 0.0, 0.0, 0.0,
    1.0, 1.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 0.0, 0.0,
    1.0, 1.0, 1.0, 1.0, 1.0,
};

//Desenhos Luan Evangelista dos Santos ------->
int creeper[5][5][3] = {
    {{0, 255, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}},
    {{0, 255, 0}, {255, 0, 0}, {0, 255, 0}, {255, 0, 0}, {0, 255, 0}},
    {{0, 255, 0}, {0, 255, 0}, {255, 0, 0}, {0, 255, 0}, {0, 255, 0}},
    {{0, 255, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {0, 255, 0}},
    {{0, 255, 0}, {255, 0, 0}, {0, 255, 0}, {255, 0, 0}, {0, 255, 0}}
};
int creeper1[5][5][3] = {
    {{0, 255, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}},
    {{0, 255, 0}, {255, 0, 0}, {0, 255, 0}, {255, 0, 0}, {0, 255, 0}},
    {{0, 255, 0}, {0, 255, 0}, {255, 0, 0}, {0, 255, 0}, {0, 255, 0}},
    {{0, 255, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {0, 255, 0}},
    {{0, 255, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}}
};
int creeper2[5][5][3] ={
    {{0, 255, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}},
    {{0, 255, 0}, {255, 0, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}},
    {{0, 255, 0}, {0, 255, 0}, {255, 0, 0}, {0, 255, 0}, {0, 255, 0}},
    {{0, 255, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {0, 255, 0}},
    {{0, 255, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}}
};
int creeper3[5][5][3] = {
    {{0, 255, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}},
    {{0, 255, 0}, {255, 0, 0}, {0, 255, 0}, {255, 0, 0}, {0, 255, 0}},
    {{0, 255, 0}, {0, 255, 0}, {255, 0, 0}, {0, 255, 0}, {0, 255, 0}},
    {{0, 255, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {0, 255, 0}},
    {{0, 255, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}}
};
int creeper4[5][5][3] = {
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {255, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}
};
int creeper5[5][5][3] ={
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {255, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {255, 0, 0}, {0, 0, 0}, {255, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {255, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}
};
int creeper6[5][5][3] = {
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {255, 0, 0}, {0, 0, 0}, {255, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {255, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}
};
int creeper7[5][5][3] = {
    {{0, 0, 0}, {255, 0, 0}, {0, 0, 0}, {255, 0, 0}, {0, 0, 0}},
    {{255, 0, 0}, {0, 0, 0}, {255, 0, 0}, {0, 0, 0}, {255, 0, 0}},
    {{255, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 0, 0}},
    {{0, 0, 0}, {255, 0, 0}, {0, 0, 0}, {255, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {255, 0, 0}, {0, 0, 0}, {0, 0, 0}}
};
/*
ANIMAÇÃO ÁTILA CONCEIÇÃO DE GOES
*/

int frame01Poke[5][5][3] = {
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 255, 255}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{253, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}
    // frame 1


};
int frame02Poke[5][5][3] = {
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 255, 255}, {255, 255, 255}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{253, 0, 0}, {253, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}
    // frame 2

    
};
int frame03Poke[5][5][3] = {
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{253, 0, 0}, {253, 0, 0}, {253, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}
    // frame 3

    
};
int frame04Poke[5][5][3] = {
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}},
    {{0, 0, 0}, {255, 255, 255}, {0, 0, 0}, {253, 0, 0}, {0, 0, 0}},
    {{253, 0, 0}, {253, 0, 0}, {253, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}
    //frame 4

    
};
int frame05Poke[5][5][3] = {
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {255, 255, 255}, {253, 0, 0}, {255, 255, 255}},
    {{0, 0, 0}, {255, 255, 255}, {0, 0, 0}, {253, 0, 0}, {0, 0, 0}},
    {{253, 0, 0}, {255, 255, 255}, {253, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}
    // frame 5

    
};
int frame06Poke[5][5][3] = {
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {253, 0, 0}, {253, 0, 0}, {255, 255, 255}},
    {{0, 0, 0}, {255, 255, 255}, {0, 0, 0}, {253, 0, 0}, {0, 0, 0}},
    {{253, 0, 0}, {255, 255, 255}, {255, 255, 255}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}
    // frame 6

    
};
int frame07Poke[5][5][3] = {
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {253, 0, 0}, {253, 0, 0}, {253, 0, 0}, {255, 255, 255}},
    {{0, 0, 0}, {255, 255, 255}, {0, 0, 0}, {253, 0, 0}, {0, 0, 0}},
    {{253, 0, 0}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}
    // frame 7

    
};
int frame08Poke[5][5][3] = {
    {{0, 0, 0}, {253, 0, 0}, {253, 0, 0}, {253, 0, 0}, {0, 0, 0}},
    {{253, 0, 0}, {253, 0, 0}, {253, 0, 0}, {253, 0, 0}, {253, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {255, 255, 255}, {0, 0, 0}, {0, 0, 0}},
    {{255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}},
    {{0, 0, 0}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {0, 0, 0}}
    // frame 8

    
};
int frame09Poke[5][5][3] = {
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}
    // frame 9

    
};
int frame10Poke[5][5][3] = {
    {{0, 0, 0}, {253, 0, 0}, {253, 0, 0}, {253, 0, 0}, {0, 0, 0}},
    {{253, 0, 0}, {253, 0, 0}, {253, 0, 0}, {253, 0, 0}, {253, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {255, 255, 255}, {0, 0, 0}, {0, 0, 0}},
    {{255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}},
    {{0, 0, 0}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {0, 0, 0}}
    // frame 10

    
};
int frame11Poke[5][5][3] = {
     {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}
    // frame 11

    
};
int frame12Poke[5][5][3] = {
    {{0, 0, 0}, {253, 0, 0}, {253, 0, 0}, {253, 0, 0}, {0, 0, 0}},
    {{253, 0, 0}, {253, 0, 0}, {253, 0, 0}, {253, 0, 0}, {253, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {255, 255, 255}, {0, 0, 0}, {0, 0, 0}},
    {{255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}},
    {{0, 0, 0}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {0, 0, 0}}
    // frame 12


     
};
/////////////////////////////////////////////////////////////////////

//Animacao Breno Novais Couto
int love01 [5][5][3] = {
    {{255, 0, 0}, {0, 19, 255}, {0, 19, 255}, {0, 19, 255}, {0, 19, 255}},
    {{255, 0, 0}, {0, 19, 255}, {0, 19, 255}, {0, 19, 255}, {0, 19, 255}},
    {{255, 0, 0}, {0, 19, 255}, {0, 19, 255}, {0, 19, 255}, {0, 19, 255}},
    {{255, 0, 0}, {0, 19, 255}, {0, 19, 255}, {0, 19, 255}, {0, 19, 255}},
    {{255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}}
};

int love02 [5][5][3] = {
    {{0, 19, 255}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {0, 19, 255}},      
    {{255, 0, 0}, {0, 19, 255}, {0, 19, 255}, {0, 19, 255}, {255, 0, 0}},     
    {{255, 0, 0}, {0, 19, 255}, {0, 19, 255}, {0, 19, 255}, {255, 0, 0}},     
    {{255, 0, 0}, {0, 19, 255}, {0, 19, 255}, {0, 19, 255}, {255, 0, 0}},     
    {{0, 19, 255}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {0, 19, 255}}
};

int love03 [5][5][3] = {
    {{255, 0, 0}, {0, 19, 255}, {0, 19, 255}, {0, 19, 255}, {255, 0, 0}},     
    {{255, 0, 0}, {0, 19, 255}, {0, 19, 255}, {0, 19, 255}, {255, 0, 0}},     
    {{255, 0, 0}, {0, 19, 255}, {0, 19, 255}, {0, 19, 255}, {255, 0, 0}},
    {{0, 19, 255}, {255, 0, 0}, {0, 19, 255}, {255, 0, 0}, {0, 19, 255}},     
    {{0, 19, 255}, {0, 19, 255}, {255, 0, 0}, {0, 19, 255}, {0, 19, 255}}     
};

int love04 [5][5][3] = {
    {{255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}},        
    {{255, 0, 0}, {0, 19, 255}, {0, 19, 255}, {0, 19, 255}, {0, 19, 255}},    
    {{255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {0, 19, 255}},       
    {{255, 0, 0}, {0, 19, 255}, {0, 19, 255}, {0, 19, 255}, {0, 19, 255}},    
    {{255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}}
};

int love05 [5][5][3] = {
    {{0, 19, 255}, {255, 0, 0}, {0, 19, 255}, {255, 0, 0}, {0, 19, 255}},     
    {{255, 0, 0}, {0, 19, 255}, {255, 0, 0}, {0, 19, 255}, {255, 0, 0}},      
    {{255, 0, 0}, {0, 19, 255}, {0, 19, 255}, {0, 19, 255}, {255, 0, 0}},     
    {{0, 19, 255}, {255, 0, 0}, {0, 19, 255}, {255, 0, 0}, {0, 19, 255}},     
    {{0, 19, 255}, {0, 19, 255}, {255, 0, 0}, {0, 19, 255}, {0, 19, 255}}
};

/////////////////////////////////////////////////////////////////////

// Animacao Alana Reis

int coracao1[5][5][3] = {
    {{0, 0, 0}, {0, 0, 255}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 255}, {0, 0, 255}, {0, 0, 255}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 255}, {0, 0, 255}, {0, 0, 255}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 255}, {0, 0, 255}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 255}, {0, 0, 0}, {0, 0, 0}}
    };
 int coracao2[5][5][3] = {
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 255}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 255}, {0, 0, 255}, {0, 0, 255}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 255}, {0, 0, 255}, {0, 0, 255}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 255}, {0, 0, 255}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 255}, {0, 0, 0}, {0, 0, 0}}
};
 int coracao3[5][5][3] = {
    {{0, 0, 0}, {0, 0, 255}, {0, 0, 0}, {0, 0, 255}, {0, 0, 0}},
    {{0, 0, 255}, {0, 0, 255}, {0, 0, 255}, {0, 0, 255}, {0, 0, 255}},
    {{0, 0, 255}, {0, 0, 255}, {0, 0, 255}, {0, 0, 255}, {0, 0, 255}},
    {{0, 0, 0}, {0, 0, 255}, {0, 0, 255}, {0, 0, 255}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 255}, {0, 0, 0}, {0, 0, 0}}
};

///////////////////////////////////////////////////////////////////

// Definição de pixel GRB
struct pixel_t {
 uint8_t G, R, B; // Três valores de 8-bits compõem um pixel.
};
typedef struct pixel_t pixel_t;
typedef pixel_t npLED_t; // Mudança de nome de "struct pixel_t" para "npLED_t" por clareza.

// Declaração do buffer de pixels que formam a matriz.
npLED_t leds[LED_COUNT];

// Variáveis para uso da máquina PIO.
PIO np_pio;
uint sm;

// Declaração de funções
char get_key();
void keypad_init();
void control_ledsebuzz(char key);
void npInit(uint pin);
void npSetLED(const uint index, const uint8_t r, const uint8_t g, const uint8_t b);
void npClear();
void npWrite();
int getIndex(int x, int y);
void npSetPattern(int matriz[5][5][3]);


int main() {
 // Inicializa entradas e saídas.
 stdio_init_all();

// Inicializa o teclado e os LEDs
keypad_init();

 // Inicializa matriz de LEDs NeoPixel.
 npInit(LED_PIN);
 npClear(); //limpa o buffer de pixel
 npWrite(); //envia o comando para a matrix de led

 printf("Teclado Matricial 4x4 - Controle de Matrix 5x5 de LEDs\n");

 while (true) {

     {
        char key = get_key(); // Lê a tecla pressionada
        // Verifica se a tecla é válida (diferente de '\0')
        if (key != '\0')
        {
            printf("Tecla pressionada: %c\n", key);

            // Se a tecla pressionada for '*', sair do loop e iniciar modo bootsel
            if (key == '*')
            {
                printf("Loop interrompido.\n");
                npClear(); 
                npWrite(); 
                reset_usb_boot(0,0); //habilita o modo bootsel
            }

            control_ledsebuzz(key); // Controla os LEDs e o buzzer com base na tecla
        }

        sleep_ms(100); // Pequena pausa para evitar leituras repetidas
    }
 }
}

// Função para ler a tecla pressionada
char get_key()
{
    int linhas[] = {LIN_1, LIN_2, LIN_3, LIN_4};
    int colunas[] = {COL_1, COL_2, COL_3, COL_4};

    for (int l = 0; l < 4; l++)
    {
        gpio_put(linhas[l], false); // Ativa a linha atual
        for (int c = 0; c < 4; c++)
        {
            if (!gpio_get(colunas[c]))
            {                 // Verifica se a coluna está em nível baixo
                sleep_ms(10); // Debounce
                if (!gpio_get(colunas[c]))
                {                              // Confirma o pressionamento
                    gpio_put(linhas[l], true); // Desativa a linha
                    return key_map[l][c];
                }
            }
        }
        gpio_put(linhas[l], true); // Desativa a linha atual
    }
    return '\0'; // Nenhuma tecla pressionada
}

// Inicializa os pinos do teclado
void keypad_init()
{
    // Arrays com os pinos das linhas e colunas
    int linhas[] = {LIN_1, LIN_2, LIN_3, LIN_4};
    int colunas[] = {COL_1, COL_2, COL_3, COL_4};

    // Configura as linhas como saída e inicializa em nível alto
    for (int i = 0; i < 4; i++)
    {
        gpio_init(linhas[i]);
        gpio_set_dir(linhas[i], GPIO_OUT);
        gpio_put(linhas[i], true); // Nível alto
    }

    // Configura as colunas como entrada com pull-up
    for (int i = 0; i < 4; i++)
    {
        gpio_init(colunas[i]);
        gpio_set_dir(colunas[i], GPIO_IN);
        gpio_pull_up(colunas[i]); // Ativa pull-up
    }
}

/**
* Inicializa a máquina PIO para controle da matriz de LEDs.
*/
void npInit(uint pin) {

 // Cria programa PIO.
 uint offset = pio_add_program(pio0, &ws2818b_program);
 np_pio = pio0;

 // Toma posse de uma máquina PIO.
 sm = pio_claim_unused_sm(np_pio, false);
 if (sm < 0) {
   np_pio = pio1;
   sm = pio_claim_unused_sm(np_pio, true); // Se nenhuma máquina estiver livre, panic!
 }

 // Inicia programa na máquina PIO obtida.
 ws2818b_program_init(np_pio, sm, offset, pin, 800000.f);

 // Limpa buffer de pixels.
 for (uint i = 0; i < LED_COUNT; ++i) {
   leds[i].R = 0;
   leds[i].G = 0;
   leds[i].B = 0;
 }
}

/**
* Atribui uma cor RGB a um LED.
*/
void npSetLED(const uint index, const uint8_t r, const uint8_t g, const uint8_t b) {
 leds[index].R = r;
 leds[index].G = g;
 leds[index].B = b;
}

/**
* Limpa o buffer de pixels.
*/
void npClear() {
 for (uint i = 0; i < LED_COUNT; ++i)
   npSetLED(i, 0, 0, 0);
}

/**
* Escreve os dados do buffer nos LEDs.
*/
void npWrite() {
 // Escreve cada dado de 8-bits dos pixels em sequência no buffer da máquina PIO.
 for (uint i = 0; i < LED_COUNT; ++i) {
   pio_sm_put_blocking(np_pio, sm, leds[i].G);
   pio_sm_put_blocking(np_pio, sm, leds[i].R);
   pio_sm_put_blocking(np_pio, sm, leds[i].B);
 }
}

int getIndex(int x, int y) {
    // Se a linha for par (0, 2, 4), percorremos da esquerda para a direita.
    // Se a linha for ímpar (1, 3), percorremos da direita para a esquerda.
    if (y % 2 == 0) {
        return y * 5 + x; // Linha par (esquerda para direita).
    } else {
        return y * 5 + (4 - x); // Linha ímpar (direita para esquerda).
    }
}

/**
 * Função para acender os LEDs com base nas matrizes de desenho.
 * LEDs com valor 1 no vetor serão acesos com a cor especificada.
 */
void npSetPattern(int matriz[5][5][3]) {
    int index = 0; // Índice para mapear a matriz 2D para o vetor linear de LEDs (0 a 24)
int conversao[5][5][3]=
{
    {{matriz[4][4][0],matriz[4][4][1], matriz[4][4][2]},{matriz[4][3][0],matriz[4][3][1], matriz[4][3][2]}, {matriz[4][2][0],matriz[4][2][1], matriz[4][2][2]}, {matriz[4][1][0],matriz[4][1][1], matriz[4][1][2]}, {matriz[4][0][0],matriz[4][0][1], matriz[4][0][2]}},
    {{matriz[3][0][0],matriz[3][0][1], matriz[3][0][2]}, {matriz[3][1][0],matriz[3][1][1], matriz[3][1][2]}, {matriz[3][2][0],matriz[3][2][1], matriz[3][2][2]}, {matriz[3][3][0],matriz[3][3][1], matriz[3][3][2]}, {matriz[3][4][0],matriz[3][4][1], matriz[3][4][2]}},
    {{matriz[2][4][0],matriz[2][4][1], matriz[2][4][2]}, {matriz[2][3][0],matriz[2][3][1], matriz[2][3][2]}, {matriz[2][2][0],matriz[2][2][1], matriz[2][2][2]}, {matriz[2][1][0],matriz[2][1][1], matriz[2][1][2]}, {matriz[2][0][0],matriz[2][0][1], matriz[2][0][2]}},
    {{matriz[1][0][0],matriz[1][0][1], matriz[1][0][2]},{matriz[1][1][0],matriz[1][1][1], matriz[1][1][2]}, {matriz[1][2][0],matriz[1][2][1], matriz[1][2][2]}, {matriz[1][3][0],matriz[1][3][1], matriz[1][3][2]}, {matriz[1][4][0],matriz[1][4][1], matriz[1][4][2]}},
    {{matriz[0][4][0],matriz[0][4][1], matriz[0][4][2]}, {matriz[0][3][0],matriz[0][3][1], matriz[0][3][2]}, {matriz[0][2][0],matriz[0][2][1], matriz[0][2][2]}, {matriz[0][1][0],matriz[0][1][1], matriz[0][1][2]}, {matriz[0][0][0],matriz[0][0][1], matriz[0][0][2]}}
};


    for (int linha = 0; linha < 5; linha++) {
        for (int coluna = 0; coluna < 5; coluna++) {
            int r = conversao[linha][coluna][0]; // Componente R
            int g = conversao[linha][coluna][1]; // Componente G
            int b = conversao[linha][coluna][2]; // Componente B

            // Acende o LED na posição correspondente
            npSetLED(index, r, g, b);
            index++;
        }
    }
    npWrite(); // Envia os dados para a matriz de LEDs
}

// Função para controlar os LEDs e buzzer
void control_ledsebuzz(char key)
{
    if (key == '0')
    {
        npSetPattern(T);
        sleep_ms(1000);
        npSetPattern(E);
        sleep_ms(1000);
        npSetPattern(S);
        sleep_ms(1000);
        npSetPattern(T);
        sleep_ms(1000);
        npSetPattern(E);
        sleep_ms(1000);
    }else if(key == '1'){
        
        npSetPattern(creeper);
        sleep_ms(200);
        npSetPattern(creeper2);
        sleep_ms(200);
        npSetPattern(creeper3);
        sleep_ms(200);
        npSetPattern(creeper4);
        sleep_ms(200);
        npSetPattern(creeper5);
        sleep_ms(200);
        npSetPattern(creeper6);
        sleep_ms(200);
        npSetPattern(creeper7);
        sleep_ms(200);
    }
        if (key == 'A')
    {
        npClear(); //Apaga todos os leds
        npWrite(); // Envia os dados para apagar os LEDs
    }
    if (key == '5'){

        npSetPattern(frame01Poke);
        sleep_ms(1000);
        npSetPattern(frame02Poke);
        sleep_ms(1000);
        npSetPattern(frame03Poke);
        sleep_ms(1000);
        npSetPattern(frame04Poke);
        sleep_ms(1000);
        npSetPattern(frame05Poke);
        sleep_ms(1000);
        npSetPattern(frame06Poke);
        sleep_ms(1000);
        npSetPattern(frame07Poke);
        sleep_ms(1000);
        npSetPattern(frame08Poke);
        sleep_ms(1000);
        npSetPattern(frame09Poke);
        sleep_ms(1000);
        npSetPattern(frame10Poke);
        sleep_ms(1000);
        npSetPattern(frame11Poke);
        sleep_ms(1000);
        npSetPattern(frame12Poke);
        sleep_ms(1000);
    }
    
    if (key == '9'){

        npSetPattern(love01);
        sleep_ms(400);
        npSetPattern(love02);
        sleep_ms(400);
        npSetPattern(love03);
        sleep_ms(400);
        npSetPattern(love04);
        sleep_ms(400);
        npSetPattern(love05);
        sleep_ms(400);
    }

    if (key == '2'){
        npSetPattern(coracao1);
        sleep_ms(1500);
        npSetPattern(coracao2);
        sleep_ms(1500);
        npSetPattern(coracao3);
        sleep_ms(1500);
    }

    if (key == 'B')
    {
   for(int i = 0; i < 25; i++) 
    {   

        npSetLED(i, 0, 0, 255); //define qual pixel será ligado e sua cor 
    } 
      npWrite(); //envia o comando para a matrix
    }

      if (key == 'C')
    {
   for(int i = 0; i < 25; i++) 
    {   

        npSetLED(i, 204, 0, 0); //define qual pixel será ligado e sua cor 
    } 
        npWrite(); //envia o comando para a matrix
    }

          if (key == 'D')
    {
   for(int i = 0; i < 25; i++) 
    {   
        npSetLED(i, 0, 127, 0); //define qual pixel será ligado e sua cor 
    } 
    npWrite(); //envia o comando para a matrix
    }

              if (key == '#')
    {
   for(int i = 0; i < 25; i++) 
    {   
        npSetLED(i, 255, 255, 255); //define qual pixel será ligado e sua cor 
    } 
    npWrite(); //envia o comando para a matrix
    }
}
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
double T[25] = { 
    1.0, 1.0, 1.0, 1.0, 1.0,
    0.0, 0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0, 0.0,
};
double E[25] = { 
    1.0, 1.0, 1.0, 1.0, 1.0,
    1.0, 0.0, 0.0, 0.0, 0.0,
    1.0, 1.0, 1.0, 1.0, 1.0,
    1.0, 0.0, 0.0, 0.0, 0.0,
    1.0, 1.0, 1.0, 1.0, 1.0,
};

double S[25] = { 
    1.0, 1.0, 1.0, 1.0, 1.0,
    1.0, 0.0, 0.0, 0.0, 0.0,
    1.0, 1.0, 1.0, 1.0, 1.0,
    0.0, 0.0, 0.0, 0.0, 1.0,
    1.0, 1.0, 1.0, 1.0, 1.0,
};

double um[25] = { 
    0.0, 1.0, 0.0, 0.0, 0.0,
    1.0, 1.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 0.0, 0.0,
    1.0, 1.0, 1.0, 1.0, 1.0,
};

double dois[25] = { 
    1.0, 1.0, 1.0, 1.0, 1.0,
    0.0, 0.0, 0.0, 0.0, 1.0,
    1.0, 1.0, 1.0, 1.0, 1.0,
    1.0, 0.0, 0.0, 0.0, 0.0,
    1.0, 1.0, 1.0, 1.0, 1.0,
};

double tres[25] = { 
    1.0, 1.0, 1.0, 1.0, 1.0,
    0.0, 0.0, 0.0, 0.0, 1.0,
    0.0, 1.0, 1.0, 1.0, 1.0,
    0.0, 0.0, 0.0, 0.0, 1.0,
    1.0, 1.0, 1.0, 1.0, 1.0,
};




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
void npSetPattern(double desenho[25],  uint8_t r, uint8_t g, uint8_t b);



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


 // Não faz mais nada. Loop infinito.
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
void npSetPattern(double desenho[25], uint8_t r, uint8_t g, uint8_t b) {
    double conversao[25] = { 
        desenho[24], desenho[23], desenho[22], desenho[21], desenho[20],
        desenho[15], desenho[16], desenho[17], desenho[18], desenho[19],
        desenho[14], desenho[13], desenho[12], desenho[11], desenho[10],
        desenho[5], desenho[6], desenho[7], desenho[8], desenho[9],
        desenho[4], desenho[3], desenho[2], desenho[1], desenho[0]
    };
    
    for (int i = 0; i < 25; i++) {
        if (conversao[i] > 0.0) { // Acende apenas os LEDs indicados pelo vetor
            npSetLED(i, r, g, b);
        } else { // Desliga os LEDs restantes
            npSetLED(i, 0, 0, 0);
        }
    }
    npWrite(); // Envia os dados para a matriz de LEDs
}









// Função para controlar os LEDs e buzzer
void control_ledsebuzz(char key)
{

            if (key == '0')
    {
  npSetPattern(T, 255, 255, 255);
     sleep_ms(1000);
     npSetPattern(E, 255, 255, 255);
     sleep_ms(1000);
     npSetPattern(S, 255, 255, 255);
     sleep_ms(1000);
     npSetPattern(T, 255, 255, 255);
     sleep_ms(1000);
     npSetPattern(E, 255, 255, 255);
     sleep_ms(1000);
     npSetPattern(um, 255, 255, 255);
     sleep_ms(1000);
     npSetPattern(dois, 255, 255, 255);
     sleep_ms(1000);
     npSetPattern(tres, 255, 255, 255);
     sleep_ms(1000);

    }
                if (key == '9')
    {
        npSetLED(6, 0, 0, 255); //define qual pixel será ligado e sua cor
        npWrite(); // Envia os dados para apagar os LEDs
    }
        if (key == 'A')
    {
        npClear(); //Apaga todos os leds
        npWrite(); // Envia os dados para apagar os LEDs
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
# Controle de Matriz de LEDs e Teclado Matricial com Raspberry Pi Pico W

## Resumo do Código

Este projeto implementa um sistema para controlar uma matriz de LEDs (5x5) e um teclado matricial 4x4 utilizando o microcontrolador **Raspberry Pi Pico W (RP2040)**. O sistema gerencia os LEDs e detecta teclas pressionadas, permitindo interações e animações personalizadas.

---

## Funcionalidades

### **1. Teclado Matricial 4x4**
- Configuração das linhas e colunas para detectar teclas pressionadas.
- Cada tecla ativa uma funcionalidade ou animação específica.

### **2. Controle de LEDs NeoPixel**
- Utiliza uma máquina PIO (*Programmable I/O*) para gerar sinais precisos.
- Permite controle individual das cores e intensidades dos LEDs.

### **3. Matriz de LEDs 5x5**
- As teclas pressionadas acionam padrões de luz na matriz de LEDs.
- Possibilidade de criar animações personalizadas.

### **4. Modo Bootsel**
- Pressionando a tecla `*`, o microcontrolador reinicia no modo "Bootsel", permitindo reprogramação via USB.

---

## Modos Especiais

| **Tecla** | **Função**                                     |
|-----------|-----------------------------------------------|
| `A`       | Desliga todos os LEDs.                       |
| `B`       | Liga todos os LEDs na cor azul (100% brilho).|
| `C`       | Liga todos os LEDs na cor vermelha (80% brilho).|
| `D`       | Liga todos os LEDs na cor verde (50% brilho).|
| `#`       | Liga todos os LEDs na cor branca (20% brilho).|

---

## Animações Personalizadas

Cada tecla numérica ativa uma animação ou padrão específico na matriz de LEDs:

| **Tecla** | **Animações**                 |
|-----------|-----------------------------------------------|
| `1`       | Luan Evangelista dos Santos: ![Animação 1](https://github.com/user-attachments/assets/3bba530f-5f10-427a-ab4b-19f75a42a7da) |
| `2`       | Alana Virginia Reis Santana Santos: ![Animação 2](https://github.com/user-attachments/assets/a202537c-482c-46b8-9542-b2731cbc8314)  |
| `4`       | Camila de Araújo Bastos: ![Animação 3](https://github.com/user-attachments/assets/ad4411ef-748a-42c8-8437-78a35006b83a)  |
| `5`       | Átila Conceição De Goes: ![Animação 4](https://github.com/user-attachments/assets/b96f293d-266d-4c6d-ad93-ab8735414c1f)|

---
## Vídeo Demonstrativo

Confira o funcionamento do projeto no vídeo abaixo:  

https://youtu.be/x38TSwMcSXA

---

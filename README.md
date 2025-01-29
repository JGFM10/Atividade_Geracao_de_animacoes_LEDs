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
| `0`       | João Gabriel Furtado:  ![Animação 0](https://github.com/user-attachments/assets/0cb82b74-d9f5-4a91-8ae9-76a7c25c4bab) |
| `1`       | Luan Evangelista dos Santos: ![Animação 1](https://github.com/user-attachments/assets/3bba530f-5f10-427a-ab4b-19f75a42a7da) |
| `2`       | Alana Virginia Reis Santana Santos: ![Animação 2](https://github.com/user-attachments/assets/a202537c-482c-46b8-9542-b2731cbc8314)  |
| `3`       | Humberto Henrique Santos Sardeiro: ![Animação 3](https://github.com/user-attachments/assets/ca0ea99c-c5bb-4098-9fad-b92e27254304) |
| `4`       | Camila de Araújo Bastos: ![Animação 4](https://github.com/user-attachments/assets/ad4411ef-748a-42c8-8437-78a35006b83a)  |
| `5`       | Átila Conceição De Goes: ![Animação 5](https://github.com/user-attachments/assets/b96f293d-266d-4c6d-ad93-ab8735414c1f)|
| `8`       | Humberto Alexandre Santos Sardeiro: ![Animação 8](https://github.com/user-attachments/assets/787ff2a0-41bf-4fcc-8cfe-6423c29556a2) |
| `9`       | Breno Novais Couto: ![animacao 7](https://github.com/user-attachments/assets/056c048f-9534-4a2e-b0e5-0fad13cd43e9) |

---
## Vídeo Demonstrativo

Confira o funcionamento do projeto no vídeo abaixo:  

https://youtu.be/x38TSwMcSXA

---

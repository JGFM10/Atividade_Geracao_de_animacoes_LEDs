Resumo do Código:
Este código implementa um sistema de controle de uma matriz de LEDs (5x5) e um teclado matricial 4x4. Ele utiliza o microcontrolador Raspberry Pi Pico (RP2040) para gerenciar tanto os LEDs como as teclas pressionadas.

Funcionalidades:
Teclado Matricial 4x4: O código configura as linhas e colunas do teclado e permite detectar quais teclas foram pressionadas.
Controle de LEDs NeoPixel: A matriz de LEDs é controlada por meio de uma máquina PIO (Programmable I/O) que gera os sinais necessários para acender os LEDs. As cores de cada LED são definidas individualmente.
Matriz de LEDs 5x5: As teclas pressionadas no teclado permitem acionar padrões de luz na matriz de LEDs. Existe um controle para acender LEDs em padrões específicos, formando animações.
Modo Bootsell: Se a tecla '*' for pressionada, o sistema entra no modo "bootsel", reiniciando o microcontrolador e permitindo reprogramação via USB.

Vídeo demonstrando seu funcionamento:

Exemplo de animação presente no projeto:
**Animações em gif:**

![New Piskel (1)](https://github.com/user-attachments/assets/3bba530f-5f10-427a-ab4b-19f75a42a7da)

Luan Evangelista dos Santos

![GifPoke](https://github.com/user-attachments/assets/b96f293d-266d-4c6d-ad93-ab8735414c1f)

Átila Conceição De Goes

![coracao](https://github.com/user-attachments/assets/a202537c-482c-46b8-9542-b2731cbc8314)

Alana Virginia Reis Santana Santos

![NewPiskel](https://github.com/user-attachments/assets/ad4411ef-748a-42c8-8437-78a35006b83a)

Camila de Araújo Bastos


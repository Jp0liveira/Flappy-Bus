#include <iostream>
#include "main_includes.h"

int main() {
    FlappyBus player1; // Usa o construtor padrão
    FlappyBus player2(5, 1.5, "Alice"); // Usa o construtor com parâmetros

    player1.jump();
    player1.update();

    player2.jump();
    player2.update();

    player1.displayInfo();
    player2.displayInfo();

    return 0;
}

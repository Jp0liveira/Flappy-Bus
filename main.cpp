#include <iostream>
#include "main_includes.h"

int main() {
    // Crie uma instância de GameManager
    GameManager game;

    // Inicie o jogo
    game.startGame();

    // Registre algumas vitórias no histórico
    game.registerWin("Jogador1");
    game.registerWin("Jogador2");
    game.registerWin("Jogador3");

    // Exiba o histórico de vitórias
    game.displayWinHistory();

    return 0;

}

#include <iostream>
#include "main_includes.h"

int main() {
     // Crie um objeto FlappyBus
    FlappyBus player(5, 0.5, "Joao");

    // Simule alguns eventos do jogo
    player.addEvent("Iniciando o jogo");
    player.jump(); // Simula um salto
    player.addEvent("Jogador pulou");

    // Exiba informações do jogador e o registro de eventos
    std::cout << "Informacoes do jogador:\n";
    std::cout << player << std::endl;
    
    // Registro de Eventos do jogo
    player.displayEventLog();

    return 0;

}

#include <iostream>
#include "main_includes.h"

int main() {
    // Uso da classe FlappyBus
    FlappyBus player1; // Usa o construtor padrão
    FlappyBus player2(5, 1.5, "Alice"); // Usa o construtor com parâmetros

    // Uso da classe BusObstacle
    BusObstacle obstacle1(10, "Carro", 3);
    const BusObstacle obstacle2(15, "Caminhao", 4); // Objeto CONST

    // Uso da classe ScoreManager
    ScoreManager score1;
    const ScoreManager score2(200); // Objeto CONST

    // Uso da classe FlappyBus |  Simulação de pulos e atualizações
    player1.jump();
    player1.update();
    player1.displayInfo();

    player2.jump();
    player2.update();
    player2.displayInfo();
    
    // Uso da classe BusObstacle | Verificando colisões
    obstacle1.move(12);
    if (player1.isCollision(obstacle1)) {
        std::cout << "Player 1 collided with obstacle 1!" << std::endl;
        obstacle1.displayInfo();
    }
    
    // Verificando colisões objeto obstacle2 com objeto obstacle1
    obstacle2.checkCollision(obstacle1);
    // obstacle2.move(18); // Geraria um erro, pois o objeto é CONST

    if (player2.isCollision(obstacle2)) {
        std::cout << "Player 2 collided with obstacle 2!" << std::endl;
    }
    
    // Uso da classe ScoreManager
    score1.increaseScore();
    score1.increaseScore();
    score1.increaseScore();

    // Exibindo as informações
    player1.displayInfo();
    std::cout << "Pontuacao Atual 1: " << score1.getCurrentScore() << std::endl;
    std::cout << "Pontuacao maxima 1: " << score1.getMaxScore() << std::endl;
    
    player2.displayInfo();
    std::cout << "Pontuacao Atual 2: " << score2.getCurrentScore() << std::endl;
    std::cout << "Pontuacao maxima 2: " << score2.getMaxScore() << std::endl;

    return 0;
}

#include <iostream>
#include "main_includes.h"

int main() {
    // Uso da classe FlappyBus
    FlappyBus player1; 
    FlappyBus player2(0.5, 2, "Alice"); 
    
    FlappyBus player3(player2);
    player3.displayInfo();

    player2.setPlayerName("Bob");

    int position1 = player1.getPosition();
    double velocity1 = player1.getVelocity();
    std::cout << position1 << std::endl;
    std::cout << velocity1 << std::endl;
    player1.setPosition(20);
    player2.setVelocity(2.0);
    player1.displayInfo();

    bool collisionResult = player1.didCollide(player1.getPosition(), player1.getVelocity());

    if (collisionResult) {
        std::cout << "Jogador 1 Colidiu!" << std::endl;
    } else {
        std::cout << "Jogador 1 Nao Colidiu!" << std::endl;
    }

    player2.jump();
    player2.displayInfo();
    player2.jump();
    player2.displayInfo();
    
    return 0;
}

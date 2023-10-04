#include <iostream>
#include "main_includes.h"

int main() {
    // Uso da classe FlappyBus

    FlappyBus player(0.5, 2, "Alice"); 
    ScoreManager scoreManager(100);

    FlappyBus c_flappyBus(player);
    ScoreManager c_scoreManager(scoreManager);

    std::cout << c_flappyBus.getPlayerName() << std::endl;
    std::cout << c_scoreManager.getCurrentScore() << std::endl;

    return 0;
}

#include "GameFlappyBus.h"
#include <iostream>

GameFlappyBus::GameFlappyBus(): FlappyBus( ) {}

GameFlappyBus::GameFlappyBus(const FlappyBus& player, const BusObstacle& obstacle, const ScoreManager& score): FlappyBus( player ), BusObstacle(obstacle), ScoreManager(score) {}

GameFlappyBus::~GameFlappyBus(){}

void GameFlappyBus::playGame() {
    std::cout << "Game Start!" << std::endl;

    while (!player.isCollision(obstacle)) {
        // Simulação de pulos e atualizações do jogador
        player.jump();
        player.update();
        player.displayInfo();

        // Movimento do obstáculo
        obstacle.move(12);

        // Verificação de colisão
        if (player.isCollision(obstacle)) {
            std::cout << "Player collided with the obstacle!" << std::endl;
            obstacle.displayInfo();
        }

        std::cout << std::endl;
    }

    std::cout << "Game Over!" << std::endl;
}

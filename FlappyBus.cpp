#include <iostream>
#include "FlappyBus.h"

FlappyBus::FlappyBus() : position(0), velocity(0), score(0), playerName("Player") {}

FlappyBus::FlappyBus(int initialPosition, double initialVelocity, const std::string& name)
    : position(initialPosition), velocity(initialVelocity), score(0), playerName(name) {}

int FlappyBus::getPosition() const {
    return position;
}

double FlappyBus::getVelocity() const {
    return velocity;
}

int FlappyBus::getScore() const {
    return score;
}

std::string FlappyBus::getPlayerName() const {
    return playerName;
}

void FlappyBus::setPosition(int newPosition) {
    position = newPosition;
}

void FlappyBus::setVelocity(double newVelocity) {
    velocity = newVelocity;
}

void FlappyBus::setPlayerName(const std::string& newName) {
    playerName = newName;
}

void FlappyBus::jump() {
    velocity = -2;
}

void FlappyBus::update() {
    position += velocity;
    velocity += 1;
}

bool FlappyBus::isCollision(const BusObstacle& obstacle) const {
    return obstacle.getPosition() <= 10 && position >= obstacle.getObstacleHeight() &&
           position <= obstacle.getObstacleHeight() + 5;
}

void FlappyBus::displayInfo() const {
    std::cout << "\nNome do Jogador: " << playerName << std::endl;
    std::cout << "Posicao do onibus: " << position << std::endl;
    std::cout << "Velocidade do onibus: " << velocity << std::endl;
    std::cout << "Pontuacao: " << scoreManager.getCurrentScore() << std::endl;
    std::cout << "Informacoes do Obstaculo:" << std::endl;
    obstacle.displayInfo();
}

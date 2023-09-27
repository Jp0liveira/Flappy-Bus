#include <iostream>
#include "FlappyBus.h"

FlappyBus::FlappyBus(): position(0), velocity(0), score(0), playerName("Player") {}

FlappyBus::FlappyBus(int initialPosition, double initialVelocity, const std::string& name): position(initialPosition), velocity(initialVelocity), score(0), playerName(name){}

FlappyBus::FlappyBus(const FlappyBus &c_flappyBus){
    this->playerName = c_flappyBus.playerName;
    this->position = c_flappyBus.position;
    this->velocity = c_flappyBus.velocity;
    this-> score = c_flappyBus.score;
};

FlappyBus::~FlappyBus(){}

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
    this->increaseScore();
    this->update();
    if (didCollide(this->position, this->velocity)){
        std::cout << "Colidiu!" << std::endl;
    }else{
         std::cout << "Nao colidiu!" << std::endl;
    }
}

void FlappyBus::update() {
    position += velocity;
    velocity += 1;
}

bool FlappyBus::didCollide(int position, double velocity){
    const int collisionMargin = 1;
    return abs(position - velocity) <= collisionMargin;
}

void FlappyBus::increaseScore() {
    this-> score = this->scoreManager.increaseScore();
}


void FlappyBus::displayInfo() const {
    std::cout << "\nNome do Jogador: " << playerName << std::endl;
    std::cout << "Posicao do onibus: " << position << std::endl;
    std::cout << "Velocidade do onibus: " << velocity << std::endl;
    std::cout << "Pontuacao: " << score << std::endl;
    std::cout << "Pontuacao maxima: " << scoreManager.getMaxScore() << std::endl;

}

#include <iostream>
#include "FlappyBus.h"

FlappyBus::FlappyBus(): position(5), velocity(3), score(0), playerName("Player"), eventLog(nullptr), eventLogSize(0), eventCount(0) {}

FlappyBus::FlappyBus(int initialPosition, double initialVelocity, const std::string& name): position(initialPosition), velocity(initialVelocity), score(0), playerName(name), eventLog(nullptr), eventLogSize(0), eventCount(0){}

FlappyBus::FlappyBus(const FlappyBus &c_flappyBus){
    this->playerName = c_flappyBus.playerName;
    this->position = c_flappyBus.position;
    this->velocity = c_flappyBus.velocity;
    this-> score = c_flappyBus.score;

     // Copiar o registro de eventos do jogo
    this->eventLogSize = c_flappyBus.eventLogSize;
    this->eventCount = c_flappyBus.eventCount;
    this->eventLog = new std::string[this->eventLogSize];
    for (int i = 0; i < eventCount; ++i) {
        this->eventLog[i] = c_flappyBus.eventLog[i];
    }
};

FlappyBus::~FlappyBus(){
    delete[] eventLog;
}

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

bool FlappyBus::getHadCollision(){
    return hadCollision;
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

void FlappyBus::setHadCollision(bool collision){
    hadCollision = collision;
}

int FlappyBus::MaxScore(const ScoreManager& c_scoreManager){
    return this->score = c_scoreManager.getMaxScore();
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
    if (abs(position - velocity) <= collisionMargin){
       hadCollision = true;
    }
    return hadCollision;
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

// Alocação de memória
void FlappyBus::addEvent(const std::string& eventDescription) {
    if (eventCount >= eventLogSize) {
        allocateMemory(eventLogSize + 1);
    }
    eventLog[eventCount++] = eventDescription;
}

void FlappyBus::displayEventLog() const {
    std::cout << "Registro de Eventos do Jogo:\n";
    for (int i = 0; i < eventCount; ++i) {
        std::cout << "Evento " << i + 1 << ": " << eventLog[i] << std::endl;
    }
}

void FlappyBus::allocateMemory(int newSize) {
    std::string* newEventLog = new std::string[newSize];
    for (int i = 0; i < eventCount; ++i) {
        newEventLog[i] = eventLog[i];
    }
    delete[] eventLog;
    eventLog = newEventLog;
    eventLogSize = newSize;
}

// Sobrecarga dos Operadores
FlappyBus& FlappyBus::operator=(const FlappyBus& other) {
    if (this == &other) {
        return *this;
    }

    this->position = other.position;
    this->velocity = other.velocity;
    this->score = other.score;
    this->playerName = other.playerName;
    this->hadCollision = other.hadCollision;

    return *this;
}

bool FlappyBus::operator==(const FlappyBus& other) const {
    if (this == &other) {
        return true;
    }

    return this->position == other.position &&
           this->velocity == other.velocity &&
           this->score == other.score &&
           this->playerName == other.playerName &&
           this->hadCollision == other.hadCollision;
}

bool FlappyBus::operator!=(const FlappyBus& other) const {
    return !(*this == other);
}

bool FlappyBus::operator!() const {
    return hadCollision;
}

std::ostream& operator<<(std::ostream& os, const FlappyBus& flappyBus) {
    os << "Nome do Jogador: " << flappyBus.playerName << std::endl;
    os << "Posicao do onibus: " << flappyBus.position << std::endl;
    os << "Velocidade do onibus: " << flappyBus.velocity << std::endl;
    os << "Pontuacao: " << flappyBus.score << std::endl;
    os << "Pontuacao maxima: " << flappyBus.scoreManager.getMaxScore() << std::endl;
    return os;
}


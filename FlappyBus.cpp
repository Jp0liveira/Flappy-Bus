#include <iostream>
#include "FlappyBus.h"

ObstaculoEmMovimento::ObstaculoEmMovimento(int posX, int posY, double spdX, double spdY)
    : positionX(posX), positionY(posY), speedX(spdX), speedY(spdY) {}

ObstaculoEstatico::ObstaculoEstatico(int posX, int posY, int w, int h)
    : positionX(posX), positionY(posY), width(w), height(h) {}

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
    obstaculosEmMovimento.clear();
    obstaculosEstaticos.clear();
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
    this->didCollide();
}

void FlappyBus::update() {
    position += velocity;
    velocity += 1;

    // Verica se o power-up ainda está em uso
    if (usingPowerUp) {
        std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsedSeconds = std::chrono::duration_cast<std::chrono::duration<double>>(currentTime - powerUpStartTime);

        if (elapsedSeconds >= powerUpDuration) {
            // O power-up expirou; restaurando a velocidade normal
            velocity = baseVelocity;
            usingPowerUp = false;
        }
    }
}

bool FlappyBus::didCollide() {
    const int collisionMargin = 2;

    // Verifica colisão com obstáculos em movimento
    for (const ObstaculoEmMovimento& obstaculo : obstaculosEmMovimento) {
        if (abs(position - obstaculo.positionX) <= collisionMargin) {
            if (abs(velocity - obstaculo.speedY) <= collisionMargin) {
                hadCollision = true;
                return hadCollision;
            }
        }
    }

    // Verifica colisão com obstáculos estáticos
    for (const ObstaculoEstatico& obstaculo : obstaculosEstaticos) {
        if (position >= obstaculo.positionX && position <= (obstaculo.positionX + obstaculo.width)) {
            if (abs(position - obstaculo.positionY) <= collisionMargin) {
                hadCollision = true;
                return hadCollision;
            }
        }
    }

    return hadCollision;
}

void FlappyBus::increaseScore() {
    this-> score = this->scoreManager.increaseScore();
}

void FlappyBus::displayInfo() const {
    std::cout << "\nNome: " << playerName << std::endl;
    std::cout << "Posicao: " << position << std::endl;
    std::cout << "Velocidade: " << velocity << std::endl;
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

// Uso do STL MAP
std::map<int, std::string> FlappyBus::getPlayerEvents() const {
    std::map<int, std::string> events;
    for (int i = 0; i < eventCount; ++i) {
        events[i] = eventLog[i];
    }
    return events;
}

// Uso das Structs
void FlappyBus::addObstaculoEmMovimento(int posX, int posY, double spdX, double spdY) {
    ObstaculoEmMovimento obstaculo(posX, posY, spdX, spdY);
    obstaculosEmMovimento.push_back(obstaculo);
}

void FlappyBus::addObstaculoEstatico(int posX, int posY, int w, int h) {
    ObstaculoEstatico obstaculo(posX, posY, w, h);
    obstaculosEstaticos.push_back(obstaculo);
}

// Uso da classe PoweUp
void FlappyBus::addPowerUp(const PowerUp& powerUp) {
    powerUps.push_back(powerUp);
}

void FlappyBus::usePowerUp(const PowerUp& powerUp) {
    // Verifique se o FlappyBus possui o power-up
    bool found = false;
    for (auto it = powerUps.begin(); it != powerUps.end(); ++it) {
        if (it->getName() == powerUp.getName()) {
            if (it->getName() == "SpeedBoost") {
                baseVelocity = velocity; // Armazena a velocidade normal
                velocity -= 2;
                powerUpDuration = std::chrono::seconds(powerUp.getDuration()); // Duração
                powerUpStartTime = std::chrono::steady_clock::now();
                usingPowerUp = true;
            }
            // Remove o power-up após o uso
            powerUps.erase(it);
            found = true;
            break;
        }
    }

    if (!found) {
        std::cout << "FlappyBus nao possui o power-up: " << powerUp.getName() << std::endl;
    }
}

bool FlappyBus::hasPowerUp(const std::string& powerUpName) const {
    for (const PowerUp& powerUp : powerUps) {
        if (powerUp.getName() == powerUpName) {
            return true;
        }
    }
    return false;
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
    os << "Nome: " << flappyBus.playerName << std::endl;
    os << "Posicao: " << flappyBus.position << std::endl;
    os << "Velocidade: " << flappyBus.velocity << std::endl;
    os << "Pontuacao: " << flappyBus.score << std::endl;
    os << "Pontuacao maxima: " << flappyBus.scoreManager.getMaxScore() << std::endl;
    return os;
}


#include "PowerUp.h"
PowerUp::PowerUp(): name("player"), duration(0) {}

PowerUp::PowerUp(const std::string& name, int duration) : name(name), duration(duration), powerUpHistory(nullptr), powerUpHistorySize(0), powerUpCount(0) {
    
}

PowerUp::PowerUp(const PowerUp& other) : name(other.name), duration(other.duration), powerUpHistory(nullptr), powerUpHistorySize(0), powerUpCount(0) {
    if (other.powerUpCount > 0) {
        allocateMemory(other.powerUpHistorySize);
        for (int i = 0; i < other.powerUpCount; ++i) {
            addPowerUpToHistory(other.powerUpHistory[i]);
        }
    }
}

PowerUp::~PowerUp() {
    delete[] powerUpHistory;
}
const std::string& PowerUp::getName() const {
    return name;
}

int PowerUp::getDuration() const {
    return duration;
}

void PowerUp::allocateMemory(int newSize) {
    std::string* newPowerUpHistory = new std::string[newSize];
    for (int i = 0; i < powerUpCount; ++i) {
        newPowerUpHistory[i] = powerUpHistory[i];
    }
    delete[] powerUpHistory;
    powerUpHistory = newPowerUpHistory;
    powerUpHistorySize = newSize;
}

void PowerUp::addPowerUpToHistory(const std::string& powerUpName) {
    if (powerUpCount >= powerUpHistorySize) {
        allocateMemory(powerUpHistorySize + 1);
    }
    powerUpHistory[powerUpCount++] = powerUpName;
}

void PowerUp::displayPowerUpHistory() const {
    std::cout << "Historico de Power-Ups:" << std::endl;
    for (int i = 0; i < powerUpCount; ++i) {
        std::cout << "Power-Up " << i + 1 << ": " << powerUpHistory[i] << std::endl;
    }
}

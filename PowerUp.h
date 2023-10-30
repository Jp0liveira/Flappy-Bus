#pragma once
#include <string>

class PowerUp {
public:
    PowerUp();
    PowerUp(const std::string& name, int duration);
    PowerUp(const PowerUp&);
    ~PowerUp();

    const std::string& getName() const;
    int getDuration() const;

     // Adicione um power-up ao histórico
    void addPowerUpToHistory(const std::string& powerUpName);
    void displayPowerUpHistory() const;

private:
    std::string name;
    int duration;

     // Histórico de power-ups
    std::string* powerUpHistory;
    int powerUpHistorySize;
    int powerUpCount;

    void allocateMemory(int newSize);   
};


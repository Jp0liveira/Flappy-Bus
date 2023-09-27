#pragma once
#include <string>
#include "ScoreManager.h"

class FlappyBus {

    public:
        // Construtor padrão
        FlappyBus();
        // Construtor com parâmetros
        FlappyBus(int initialPosition, double initialVelocity, const std::string& name);
        FlappyBus(const FlappyBus&);
        ~FlappyBus();

        // Getters e setters
        int getPosition() const;
        double getVelocity() const;
        int getScore() const;
        std::string getPlayerName() const;
        void setPosition(int newPosition);
        void setVelocity(double newVelocity);
        void setPlayerName(const std::string& newName);

        // Métodos adicionais
        void jump(); // Usa a classe ScoreManager
        void displayInfo() const;
        bool didCollide(int position, double velocity);
        
    private:
        int position;
        double velocity;
        int score;
        std::string playerName;
        
        // Uso da classe ScoreManager
        ScoreManager scoreManager;
        
        void update();
        void increaseScore();
        
};

#pragma once
#include <string>
#include "BusObstacle.h"
#include "ScoreManager.h"

class FlappyBus {

    public:
        // Construtor padrão
        FlappyBus();

        // Construtor com parâmetros
        FlappyBus(int initialPosition, double initialVelocity, const std::string& name);

        // Getters e setters
        int getPosition() const;
        double getVelocity() const;
        int getScore() const;
        std::string getPlayerName() const;
        void setPosition(int newPosition);
        void setVelocity(double newVelocity);
        void setPlayerName(const std::string& newName);

        // Métodos adicionais
        void jump();
        void update();
        // Usando composicao
        bool isCollision(const BusObstacle& obstacle) const;
        void displayInfo() const;

    private:
        int position;
        double velocity;
        int score;
        std::string playerName;

        // Usando composicao
        BusObstacle obstacle;
        ScoreManager scoreManager;
        
};

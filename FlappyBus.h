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
        bool getHadCollision();
        int MaxScore(const ScoreManager& );
        std::string getPlayerName() const;

        void setPosition(int);
        void setVelocity(double);
        void setPlayerName(const std::string&);
        void setHadCollision(bool);

        // Métodos adicionais
        void jump(); // Usa a classe ScoreManager
        void displayInfo() const;
        bool didCollide(int position, double velocity);
        
    private:
        int position;
        double velocity;
        int score;
        std::string playerName;
        bool hadCollision = false;
        
        // Uso da classe ScoreManager
        ScoreManager scoreManager;
        
        void update();
        void increaseScore();
        
};

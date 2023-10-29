#pragma once
#include <string>
#include "ScoreManager.h"

class FlappyBus {
         friend std::ostream& operator<<(std::ostream& os, const FlappyBus& flappyBus);
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

         // Sobrecarga de operadores
        FlappyBus& operator=(const FlappyBus& other);
        bool operator==(const FlappyBus& other) const;
        bool operator!=(const FlappyBus& other) const;
        bool operator!() const;
        
        // Métodos para registro de eventos do jogo
        void addEvent(const std::string& eventDescription);
        void displayEventLog() const;

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

        // Registro de eventos do jogo
        std::string* eventLog;
        int eventLogSize;
        int eventCount;

        void allocateMemory(int newSize);

            
};

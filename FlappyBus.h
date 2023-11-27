#pragma once
#include <string>
#include <map>
#include <vector>
#include "ScoreManager.h"
#include "PowerUp.h"
#include <chrono> // Para usar chrono para medir o tempo
#include <thread> // Para pausar a execução por um tempo
#include <fstream>
#include <sstream>
#include <cctype>
#include <iomanip>
#include <algorithm>


struct ObstaculoEmMovimento {
    int positionX;
    int positionY;
    double speedX;
    double speedY;

    ObstaculoEmMovimento(int posX, int posY, double spdX, double spdY);
};

struct ObstaculoEstatico {
    int positionX;
    int positionY;
    int width;
    int height;

    ObstaculoEstatico(int posX, int posY, int w, int h);
};

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
        bool didCollide();

         // Sobrecarga de operadores
        FlappyBus& operator=(const FlappyBus& other);
        bool operator==(const FlappyBus& other) const;
        bool operator!=(const FlappyBus& other) const;
        bool operator!() const;
        
        // Métodos para registro de eventos do jogo
        void addEvent(const std::string& eventDescription);
        void displayEventLog() const;
        
        // Uso do STL MAP
        std::map<int, std::string> getPlayerEvents() const;
        
        // Uso das Structs
        void addObstaculoEmMovimento(int posX, int posY, double spdX, double spdY);
        void addObstaculoEstatico(int posX, int posY, int w, int h);

        // Métodos para PowerUps
        void addPowerUp(const PowerUp& powerUp);
        void usePowerUp(const PowerUp& powerUp);
        bool hasPowerUp(const std::string& powerUpName) const;

        bool isUsingPowerUp() { return usingPowerUp;};

        // Métodos para carregamento de arquivos
        bool loadVariablesFromFile(const std::string& filename);
        bool processVariables(const std::map<std::string, double>& numericVariables, const std::map<std::string, std::string>& stringVariables);
        bool saveVariablesToFile(const std::string& filename) const;
        bool isNumeric(const std::string& str);

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

        // Uso das Structs
        std::vector<ObstaculoEmMovimento> obstaculosEmMovimento;
        std::vector<ObstaculoEstatico> obstaculosEstaticos;

        // Uso da classe powerUp
        std::vector<PowerUp> powerUps;
        double baseVelocity; // Velocidade normal do FlappyBus
        std::chrono::steady_clock::time_point powerUpStartTime;
        std::chrono::seconds powerUpDuration;
        bool usingPowerUp =  false;
       
};

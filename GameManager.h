#pragma once
#include <iostream>
#include "FlappyBus.h"

class GameManager {
        friend std::ostream& operator<<(std::ostream&, const GameManager&);
    public:
        // Construtores
        GameManager();
        GameManager(int, double);
        GameManager(const GameManager&);
        ~GameManager();

        // Método não get ou set
        void startGame();
        
        // Atributos estáticos
        static int gameCount;
        static double gravity;

        // Atributo const static
        static const int maxPlayers = 10;

        // Métodos estáticos
        static void printGameCount();
        static void applyGravity(FlappyBus&);

        // Métodos para histórico de vitórias
        void registerWin(const std::string&);
        void displayWinHistory() const;

        // Sobrecarga dos operadores
        GameManager& operator=(const GameManager&);
        bool operator==(const GameManager&) const;
        bool operator!=(const GameManager& ) const;
        bool operator!() const;

    private:
        // Array const static
        static const int maxLevels = 5;
        static const int levelScores[maxLevels];

        // Array não constante
        int playerScores[maxPlayers];

        // Método inline
        inline static void printWelcomeMessage() {
            std::cout << "Bem-vindo ao Flappy Bus Game!" << std::endl;
        }

        // Histórico de vitórias
        std::string* winHistory;
        int winHistorySize;
        int winCount;

        void allocateMemory(int newSize);
};


#pragma once
#include <iostream>
#include "FlappyBus.h"

class GameManager {
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
        static const int maxPlayers = 4;

        // Métodos estáticos
        static void printGameCount();
        static void applyGravity(FlappyBus&);

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
};


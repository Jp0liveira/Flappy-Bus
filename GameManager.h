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

        // Métodos estáticos
        static void printGameCount();
        static void applyGravity(FlappyBus&);

        void alocarHist();
        void cadastrarRegInHist(const GameManager& game);
        void allocateMemoryForPointers();
        
        int* getIntPointer() { return intPointer; }
        double* getDoublePointer() { return doublePointer; }

        void setIntPointer(int* ptr) { intPointer = ptr; }
        void setDoublePointer(double* ptr) { doublePointer = ptr; }

    private:

        // Atributos estáticos
        static int gameCount;
        static double gravity;

        // Atributo const static
        static const int maxPlayers = 4;
            
        // Array const static
        static const int maxLevels = 5;
        static const int levelScores[maxLevels];

        // Array não constante
        int playerScores[maxPlayers];

        // Método inline
        inline static void printWelcomeMessage() {
            std::cout << "Bem-vindo ao Flappy Bus Game!" << std::endl;
        }

        // Ponteiro para um histórico de jogos
        GameManager* history;

        const int MAXGAMESHISTORY; // Número máximo de jogos no histórico
        
        // Ponteiros
        int* intPointer;
        double* doublePointer;

        // Métodos auxiliares
        int findEmptySlot() const;
        void copyHistory(const GameManager& game);

};


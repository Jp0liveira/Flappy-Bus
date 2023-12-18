#pragma once
#include "FlappyBus.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <iomanip>
#include <algorithm>

enum CharacterClass {
    WARRIOR,
    MAGE,
    ARCHER,
};

class GameCharacter : public FlappyBus {
    public:
        GameCharacter();
        GameCharacter(int initialPosition, double initialVelocity, const std::string& name, const std::string& characterClass);
        GameCharacter(const GameCharacter& other);
        virtual ~GameCharacter();

        virtual void move() = 0;
        virtual void attack() = 0;

        const std::string& getCharacterClass() const;
        void setCharacterClass(const std::string& characterClass);

        // Métodos para leitura, processamento e salvamento de variáveis
        bool loadVariablesFromFile(const std::string& filename);
        bool processVariables(const std::map<std::string, double>& numericVariables, const std::map<std::string, std::string>& stringVariables);
        bool saveVariablesToFile(const std::string& filename) const;

    protected:
        std::string characterClass;
};

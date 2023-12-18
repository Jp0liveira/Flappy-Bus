#include "GameCharacter.h"


GameCharacter::GameCharacter() : FlappyBus(), characterClass("DefaultClass") {}

GameCharacter::GameCharacter(int initialPosition, double initialVelocity, const std::string& name, const std::string& characterClass)
    : FlappyBus(initialPosition, initialVelocity, name), characterClass(characterClass) {}

GameCharacter::GameCharacter(const GameCharacter& other) : FlappyBus(other), characterClass(other.characterClass) {}

GameCharacter::~GameCharacter() {}

const std::string& GameCharacter::getCharacterClass() const {
    return characterClass;
}

void GameCharacter::setCharacterClass(const std::string& characterClass) {
    this->characterClass = characterClass;
}

// Carregamento de arquivos
bool GameCharacter::loadVariablesFromFile(const std::string& filename) {
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file: " << filename << '\n';
        return false;
    }

    std::map<std::string, double> numericVariables;
    std::map<std::string, std::string> stringVariables;

    std::string line;
    std::string variableName;
    char equalsSign;
    std::string value;

    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        if (iss >> variableName >> equalsSign >> value && equalsSign == '=') {
            // Verifica se a string pode ser convertida para um número
            if (isNumeric(value)) {
                double numericValue = std::stod(value);
                numericVariables[variableName] = numericValue;
            } else {
                stringVariables[variableName] = value;
            }
        } else {
            std::cerr << "Error parsing line: " << line << '\n';
        }
    }
    inputFile.close();
    return processVariables(numericVariables, stringVariables);

}

bool GameCharacter::processVariables(const std::map<std::string, double>& numericVariables, const std::map<std::string, std::string>& stringVariables) {
    if (numericVariables.find("initialPosition") != numericVariables.end())
        setPosition(numericVariables.at("initialPosition"));

    if (numericVariables.find("initialVelocity") != numericVariables.end())
        setVelocity(numericVariables.at("initialVelocity"));

    if (stringVariables.find("name") != stringVariables.end())
        setPlayerName(stringVariables.at("name"));

    if (stringVariables.find("characterClass") != stringVariables.end())
        this->characterClass = stringVariables.at("characterClass");

    return true;
}

bool GameCharacter::saveVariablesToFile(const std::string& filename) const {
    std::ofstream outputFile(filename);
    if (!outputFile.is_open()) {
        std::cerr << "Error opening file for writing: " << filename << '\n';
        return false;
    }

    outputFile << "initialPosition = " << getPosition() << '\n';
    outputFile << "initialVelocity = " << getVelocity() << '\n';
    outputFile << "name = " << getPlayerName() << '\n';
    outputFile << "characterClass = " << this->characterClass << '\n';

    outputFile.close();

    return true;
}
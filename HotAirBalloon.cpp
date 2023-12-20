#include "HotAirBalloon.h"

const double HotAirBalloon::defaultMaxGasLevel = 100.0; // Valor máximo padrão
const double HotAirBalloon::minGasLevel = 0.0; // Valor mínimo permitido
double HotAirBalloon::maxGasLevel = HotAirBalloon::defaultMaxGasLevel; // Inicializa com o valor padrão

HotAirBalloon::HotAirBalloon() : FloatingObstacle(), gasLevel(maxGasLevel) {}

HotAirBalloon::HotAirBalloon(int initialPosition, double initialVelocity)
    : FloatingObstacle(initialPosition, initialVelocity), gasLevel(maxGasLevel) {}

HotAirBalloon::HotAirBalloon(const HotAirBalloon& other)
    : FloatingObstacle(other), gasLevel(other.gasLevel) {}

HotAirBalloon::~HotAirBalloon() {}

void HotAirBalloon::floatInAir() {
    // Implementação específica para flutuar no ar (herdado de FloatingObstacle)
    std::cout << "HotAirBalloon floating in the air!" << std::endl;
}

void HotAirBalloon::applyWindForce() {
    // Implementação específica para aplicar força de vento (herdado de FloatingObstacle)
    std::cout << "HotAirBalloon applying wind force!" << std::endl;
}

void HotAirBalloon::releaseGas() {
    // Implementação específica para liberar gás
    if (gasLevel > 0.0) {
        std::cout << "HotAirBalloon releasing gas!" << std::endl;
        gasLevel -= 10.0;
    } else {
        std::cout << "HotAirBalloon has no gas left!" << std::endl;
    }
}

double HotAirBalloon::setGasLevel(double newGasLevel) {
    // Verifica se o novo nível de gás está dentro dos limites
    if (newGasLevel >= minGasLevel && newGasLevel <= maxGasLevel) {
        gasLevel = newGasLevel;
    } else {
        gasLevel = minGasLevel;
    }
    return gasLevel;
}

// Sobrecarga dos operadores
HotAirBalloon& HotAirBalloon::operator=(const HotAirBalloon& other) {
    if (this == &other) {
        return *this;
    }

    // Chama o operador de atribuição da classe base (FloatingObstacle)
    FloatingObstacle::operator=(other);

    // Adiciona atributos específicos de HotAirBalloon
    this->gasLevel = other.gasLevel;

    return *this;
}

bool HotAirBalloon::operator==(const HotAirBalloon& other) const {
    if (this == &other) {
        return true;
    }

    // Compara a parte da classe base (FloatingObstacle)
    if (FloatingObstacle::operator!=(other)) {
        return false;
    }

    return this->gasLevel == other.gasLevel;
}

bool HotAirBalloon::operator!=(const HotAirBalloon& other) const {
    return !(*this == other);
}

bool HotAirBalloon::operator!() const {
    // Usa a negação da classe base (FloatingObstacle)
    return !FloatingObstacle::operator!();
}

std::ostream& operator<<(std::ostream& os, const HotAirBalloon& hotAirBalloon) {
    // Usa a sobrecarga da classe base (FloatingObstacle)
    os << static_cast<const FloatingObstacle&>(hotAirBalloon);
    os << hotAirBalloon.getObstacleTypeName() << "\n";
    os << "Gas Level: " << hotAirBalloon.gasLevel << "\n";

    return os;
}

// Carregamento de arquivos
bool HotAirBalloon::loadVariablesFromFile(const std::string& filename) {
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file: " << filename << '\n';
        return false;
    }

    std::map<std::string, double> numericVariables;
    std::map<std::string, std::string> stringVariables;
    std::map<std::string, bool> boolVariables;

    std::string line;
    std::string variableName;
    char equalsSign;
    std::string value;

    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        if (iss >> variableName >> equalsSign >> value && equalsSign == '=') {
            if (FloatingObstacle::isNumeric(value)) {
                double numericValue = std::stod(value);
                numericVariables[variableName] = numericValue;
            } else if (value == "true" || value == "false") {
                bool boolValue = (value == "true");
                boolVariables[variableName] = boolValue;
            } else {
                stringVariables[variableName] = value;
            }
        } else {
            std::cerr << "Error parsing line: " << line << '\n';
        }
    }
    inputFile.close();
    return processVariables(numericVariables, stringVariables, boolVariables);
}

bool HotAirBalloon::processVariables(const std::map<std::string, double>& numericVariables, const std::map<std::string, std::string>& stringVariables, const std::map<std::string, bool>& boolVariables) {
    if (numericVariables.find("initialPosition") != numericVariables.end())
        setPosition(numericVariables.at("initialPosition"));

    if (numericVariables.find("initialVelocity") != numericVariables.end())
        setVelocity(numericVariables.at("initialVelocity"));

    if (stringVariables.find("name") != stringVariables.end())
        setPlayerName(stringVariables.at("name"));

    if (numericVariables.find("gasLevel") != numericVariables.end())
        this->gasLevel = this->setGasLevel(numericVariables.at("gasLevel"));

    return true;
}

bool HotAirBalloon::saveVariablesToFile(const std::string& filename) const {
    std::ofstream outputFile(filename);
    if (!outputFile.is_open()) {
        std::cerr << "Error opening file for writing: " << filename << '\n';
        return false;
    }

    outputFile << "initialPosition = " << getPosition() << '\n';
    outputFile << "initialVelocity = " << getVelocity() << '\n';
    outputFile << "name = " << getPlayerName() << '\n';
    outputFile << "gasLevel = " << this->gasLevel << '\n';

    outputFile.close();

    return true;
}
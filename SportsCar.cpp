#include "SportsCar.h"

SportsCar::SportsCar() : Vehicle(), turbo(false) {}

SportsCar::SportsCar(int initialPosition, double initialVelocity, const std::string& name, int fuelCapacity, const std::string& fuelType, bool turbo)
    : Vehicle(initialPosition, initialVelocity, name, fuelCapacity, fuelType), turbo(turbo) {
}

SportsCar::SportsCar(const SportsCar& other) : Vehicle(other), turbo(other.turbo) {}

SportsCar::~SportsCar() {}

bool SportsCar::hasTurbo() const {
    return turbo;
}

void SportsCar::toggleTurbo() {
    turbo = !turbo;
    std::cout << "Turbo " << (turbo ? "ativado" : "desativado") << " para o carro esportivo."  << getPlayerName() << "\n";
}

void SportsCar::accelerateWithTurbo() {
    if (turbo) {
        setVelocity(getVelocity() + 20);
    }
}

void SportsCar::displayInfo() const {
    Vehicle::displayInfo(); 
    std::cout << "Carro esportivo\n";
    std::cout << "Turbo: " << (turbo ? "ativado" : "desativado") << "\n";
}

// Sobrecarga dos Operadores
SportsCar& SportsCar::operator=(const SportsCar& other) {
    if (this == &other) {
        return *this;
    }
    // Chama o operador de atribuição da classe base (Vehicle)
    static_cast<Vehicle&>(*this) = other;

    // Adiciona atributos específicos de SportsCar
    this->turbo = other.turbo;

    return *this;
}

bool SportsCar::operator==(const SportsCar& other) const {
    if (this == &other) {
        return true;
    }

    // Compara a parte da classe base (Vehicle)
    if (static_cast<const Vehicle&>(*this) != static_cast<const Vehicle&>(other)) {
        return false;
    }

    return this->turbo == other.turbo;
}

bool SportsCar::operator!=(const SportsCar& other) const {
    return !(*this == other);
}

bool SportsCar::operator!() const {
    // Usa a negação da classe base (Vehicle)
    return !static_cast<const Vehicle&>(*this);
}

std::ostream& operator<<(std::ostream& os, const SportsCar& sportsCar) {
    // Usa a sobrecarga da classe base (Vehicle)
    os << static_cast<const Vehicle&>(sportsCar);

    os << "Carro esportivo\n";
    os << "Turbo: " << (sportsCar.turbo ? "ativado" : "desativado") << "\n";

    return os;
}

// Carregamento de arquivos
bool SportsCar::loadVariablesFromFile(const std::string& filename) {
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
            if (Vehicle::isNumeric(value)) {
                double numericValue = std::stod(value);
                numericVariables[variableName] = numericValue;
            }else if (value == "true" || value == "false") {
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


bool SportsCar::processVariables(const std::map<std::string, double>& numericVariables, const std::map<std::string, std::string>& stringVariables, std::map<std::string, bool> boolVariables) {
    if (numericVariables.find("initialPosition") != numericVariables.end())
        setPosition(numericVariables.at("initialPosition"));

    if (numericVariables.find("initialVelocity") != numericVariables.end())
        setVelocity(numericVariables.at("initialVelocity"));

    if (stringVariables.find("name") != stringVariables.end())
        setPlayerName(stringVariables.at("name"));

    if (numericVariables.find("fuelCapacity") != numericVariables.end())
        setFuelCapacity(static_cast<int>(numericVariables.at("fuelCapacity")));

    if (stringVariables.find("fuelType") != stringVariables.end())
        setfuelType(stringVariables.at("fuelType"));

    if (boolVariables.find("turbo") != boolVariables.end())
        this->turbo = boolVariables.at("turbo");

    return true;
}

bool SportsCar::saveVariablesToFile(const std::string& filename) const {
    std::ofstream outputFile(filename);
    if (!outputFile.is_open()) {
        std::cerr << "Error opening file for writing: " << filename << '\n';
        return false;
    }

    outputFile << "initialPosition = " << getPosition() << '\n';
    outputFile << "initialVelocity = " << getVelocity() << '\n';
    outputFile << "name = " << getPlayerName() << '\n';
    outputFile << "fuelCapacity = " << getFuelCapacity() << '\n';
    outputFile << "fuelType = " << getFuelType() << '\n';
    outputFile << "turbo = " << this->turbo << '\n';

    outputFile.close();

    return true;
}

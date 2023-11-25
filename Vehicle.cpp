#include "Vehicle.h"

Vehicle::Vehicle(): FlappyBus(){
    this->setFuelCapacity(100);
    this->setfuelType("Gasolina");
}

Vehicle::Vehicle(int initialPosition, double initialVelocity, const std::string& name, int fuelCapacity, const std::string& fuelType): FlappyBus(initialPosition, initialVelocity, name), fuelType(fuelType) {
    this->setFuelCapacity(fuelCapacity);
    this->setfuelType(fuelType);
}

Vehicle::Vehicle(const Vehicle& other) : FlappyBus(other) {
    this->fuelCapacity = other.fuelCapacity;
    this->fuelType = other.fuelType;
}

Vehicle::~Vehicle() {}

void Vehicle::setFuelCapacity(int fuelCapacity){
    this->fuelCapacity = fuelCapacity;
}

int Vehicle::getFuelCapacity(){
   return fuelCapacity;
}

void Vehicle::setfuelType(const std::string& fuelType) {
    this->fuelType = fuelType;
}

std::string Vehicle::getFuelType() const {
    return fuelType;
}

void Vehicle::refuel(int amount) {
    fuelCapacity += amount;
    std::cout << FlappyBus::getPlayerName() << " foi abastecido. Nova capacidade de combustivel: " << fuelCapacity << " litros.\n";
}

void Vehicle::honk() const {
    std::cout << FlappyBus::getPlayerName() << " buzina: Honk! Honk!\n";
}

void Vehicle::displayInfo() const {
    FlappyBus::displayInfo();
    std::cout << "Capacidade de combustivel: " << this->fuelCapacity << " litros\n";
    std::cout << "Tipo de combustivel: " << this->fuelType << "\n";
}

// Sobrecarga dos Operadores
Vehicle& Vehicle::operator=(const Vehicle& other) {
    if (this == &other) {
        return *this;
    }

    // Chama o operador de atribuição da classe base (FlappyBus)
    static_cast<FlappyBus&>(*this) = other;

    this->fuelCapacity = other.fuelCapacity;
    this->fuelType = other.fuelType;

    return *this;
}

bool Vehicle::operator==(const Vehicle& other) const {
    if (this == &other) {
        return true;
    }

    // Compara a parte da classe base (FlappyBus)
    if (static_cast<const FlappyBus&>(*this) != static_cast<const FlappyBus&>(other)) {
        return false;
    }

    return this->fuelCapacity == other.fuelCapacity &&
           this->fuelType == other.fuelType;
}

bool Vehicle::operator!=(const Vehicle& other) const {
    return !(*this == other);
}

bool Vehicle::operator!() const {
    // Usa a negação da classe base (FlappyBus)
    return !static_cast<const FlappyBus&>(*this);
}

std::ostream& operator<<(std::ostream& os, const Vehicle& vehicle) {
    // Usa a sobrecarga da classe base (FlappyBus)
    os << static_cast<const FlappyBus&>(vehicle);

    os << "Capacidade de combustivel: " << vehicle.fuelCapacity << " litros\n";
    os << "Tipo de combustivel: " << vehicle.fuelType << "\n";

    return os;
}

// Carregamento de arquivos
bool isNumeric(const std::string& str) {
    return !str.empty() && std::all_of(str.begin(), str.end(), [](char c) {
        return std::isdigit(c) || c == '.' || c == '-';
    });
}

bool Vehicle::loadVariablesFromFile(const std::string& filename) {
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


bool Vehicle::processVariables(const std::map<std::string, double>& numericVariables, const std::map<std::string, std::string>& stringVariables) {
    if (numericVariables.find("initialPosition") != numericVariables.end())
        setPosition(numericVariables.at("initialPosition"));

    if (numericVariables.find("initialVelocity") != numericVariables.end())
        setVelocity(numericVariables.at("initialVelocity"));

    if (stringVariables.find("name") != stringVariables.end())
        setPlayerName(stringVariables.at("name"));

    if (numericVariables.find("fuelCapacity") != numericVariables.end())
        this->fuelCapacity = static_cast<int>(numericVariables.at("fuelCapacity"));

    if (stringVariables.find("fuelType") != stringVariables.end())
        this->fuelType = stringVariables.at("fuelType");

    return true;
}

bool Vehicle::saveVariablesToFile(const std::string& filename) const {
    std::ofstream outputFile(filename);
    if (!outputFile.is_open()) {
        std::cerr << "Error opening file for writing: " << filename << '\n';
        return false;
    }

    outputFile << "initialPosition = " << getPosition() << '\n';
    outputFile << "initialVelocity = " << getVelocity() << '\n';
    outputFile << "name = " << getPlayerName() << '\n';
    outputFile << "fuelCapacity = " << this->fuelCapacity << '\n';
    outputFile << "fuelType = " << this->fuelType << '\n';

    outputFile.close();

    return true;
}

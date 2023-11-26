#include "ElectricCar.h"


const std::string ElectricCar::fuelTypeElectric = "Eletrico";

ElectricCar::ElectricCar() : Vehicle(), batteryCapacity(0), connectorType("Type 2") {}

ElectricCar::ElectricCar(int initialPosition, double initialVelocity, const std::string& name, int fuelCapacity, int batteryCapacity, const std::string& connectorType)
    : Vehicle(initialPosition, initialVelocity, name, fuelCapacity, fuelTypeElectric), batteryCapacity(batteryCapacity), connectorType(connectorType) {}

ElectricCar::ElectricCar(const ElectricCar& other) : Vehicle(other), batteryCapacity(other.batteryCapacity), connectorType(other.connectorType) {}

ElectricCar::~ElectricCar() {}

void ElectricCar::chargeBattery(int chargeAmount) {
    if (isCharging) {
        std::cout << "O carro eletrico " << getPlayerName() << " ja esta carregando.\n";
    } else {
        isCharging = true;
        batteryCapacity += chargeAmount;
        std::cout << "Carregando o carro eletrico " << getPlayerName() << ". Capacidade de carga: " << this->batteryCapacity << " kWh\n";
    }
}

void ElectricCar::disconnectCharger() {
    if (!isCharging) {
        std::cout << "O carro eletrico "<< getPlayerName() << "nao esta carregando no momento.\n";
    } else {
        isCharging = false;
        std::cout << "Carregador desconectado. Capacidade de carga: " << batteryCapacity << " kWh\n";
    }
}

void ElectricCar::displayInfo() const {
    Vehicle::displayInfo();
    std::cout << "Capacidade de carga: " << batteryCapacity << " kWh\n";
    std::cout << "Tipo de conector: " << connectorType << "\n";
    std::cout << "Status de carregamento: " << (isCharging ? "Carregando" : "Nao esta carregando") << "\n";
}

// Sobrecarga dos Operadores
ElectricCar& ElectricCar::operator=(const ElectricCar& other) {
    if (this == &other) {
        return *this;
    }

    // Chama o operador de atribuição da classe base (Vehicle)
    static_cast<Vehicle&>(*this) = other;

    this->batteryCapacity = other.batteryCapacity;
    this->connectorType = other.connectorType;

    return *this;
}

bool ElectricCar::operator==(const ElectricCar& other) const {
    if (this == &other) {
        return true;
    }

    // Compara a parte da classe base (Vehicle)
    if (static_cast<const Vehicle&>(*this) != static_cast<const Vehicle&>(other)) {
        return false;
    }

    return this->batteryCapacity == other.batteryCapacity &&
           this->connectorType == other.connectorType;
}

bool ElectricCar::operator!=(const ElectricCar& other) const {
    return !(*this == other);
}

bool ElectricCar::operator!() const {
    // Usa a negação da classe base (Vehicle)
    return !static_cast<const Vehicle&>(*this);
}

std::ostream& operator<<(std::ostream& os, const ElectricCar& electricCar) {
    // Usa a sobrecarga da classe base (Vehicle)
    os << static_cast<const Vehicle&>(electricCar);

    os << "Capacidade da bateria: " << electricCar.batteryCapacity << " kWh\n";
    os << "Tipo de conector: " << electricCar.connectorType << "\n";

    return os;
}

// Carregamento de arquivos
bool ElectricCar::loadVariablesFromFile(const std::string& filename) {
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
            if (Vehicle::isNumeric(value)) {
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

bool ElectricCar::processVariables(const std::map<std::string, double>& numericVariables, const std::map<std::string, std::string>& stringVariables) {
    if (!Vehicle::processVariables(numericVariables, stringVariables)) {
        return false;
    }

    if (numericVariables.find("batteryCapacity") != numericVariables.end())
        this->batteryCapacity = static_cast<int>(numericVariables.at("batteryCapacity"));

    if (stringVariables.find("connectorType") != stringVariables.end())
        this->connectorType = stringVariables.at("connectorType");

    return true;
}

bool ElectricCar::saveVariablesToFile(const std::string& filename) const {
    std::ofstream outputFile(filename);
    if (!outputFile.is_open()) {
        std::cerr << "Error opening file for writing: " << filename << '\n';
        return false;
    }

    outputFile << "initialPosition = " << getPosition() << '\n';
    outputFile << "initialVelocity = " << getVelocity() << '\n';
    outputFile << "name = " << getPlayerName() << '\n';
    outputFile << "fuelCapacity = " << getFuelCapacity() << '\n';
    outputFile << "fuelType = " << this->fuelTypeElectric << '\n';
    outputFile << "batteryCapacity = " << this->batteryCapacity << '\n';
    outputFile << "connectorType = " << this->connectorType << '\n';

    outputFile.close();

    return true;
}

void ElectricCar::setBatteryCapacity(int batteryCapacity) {
    this->batteryCapacity = batteryCapacity;
}

void ElectricCar::setConnectorType(const std::string& connectorType) {
    this->connectorType = connectorType;
}

int ElectricCar::getBatteryCapacity() const {
    return batteryCapacity;
}

std::string ElectricCar::getConnectorType() const {
    return connectorType;
}

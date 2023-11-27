#include "SpaceBus.h"

// Construtores
SpaceBus::SpaceBus() : FlappyBus(), propulsionType("Unknown"), hatchOpen(false), environmentalTemperature(22.0), environmentalPressure(1.0), environmentalOxygenLevel(20.9), destination("Undefined") {}

SpaceBus::SpaceBus(int initialPosition, double initialVelocity, const std::string& name, const std::string& propulsionType): FlappyBus(initialPosition, initialVelocity, name), propulsionType(propulsionType), hatchOpen(false), environmentalTemperature(22.0), environmentalPressure(1.0), environmentalOxygenLevel(20.9), destination("Undefined") {}

SpaceBus::SpaceBus(const SpaceBus& other) : FlappyBus(other), propulsionType(other.propulsionType), hatchOpen(other.hatchOpen), environmentalTemperature(other.environmentalTemperature), environmentalPressure(other.environmentalPressure), environmentalOxygenLevel(other.environmentalOxygenLevel), destination(other.destination) {}

// Destrutor
SpaceBus::~SpaceBus() {}

// Métodos adicionais
void SpaceBus::openHatch() {
    hatchOpen = true;
    std::cout << getPlayerName() << " abriu a escotilha espacial.\n";
}

void SpaceBus::closeHatch() {
    hatchOpen = false;
    std::cout << getPlayerName() << " fechou a escotilha espacial.\n";
}

void SpaceBus::adjustEnvironmentalControl(double temperature, double pressure, double oxygenLevel) {
    environmentalTemperature = temperature;
    environmentalPressure = pressure;
    environmentalOxygenLevel = oxygenLevel;
    std::cout << getPlayerName() << " ajustou o controle ambiental.\n";
}

void SpaceBus::setDestination(const std::string& newDestination) {
    destination = newDestination;
    std::cout << getPlayerName() << " definir o destino para " << destination << ".\n";
}

void SpaceBus::navigate() {
    std::cout << getPlayerName() << " esta navegando pelo espaco para chegar a " << destination << ".\n";
}


// Sobrecargas de Operadores
SpaceBus& SpaceBus::operator=(const SpaceBus& other) {
    if (this == &other) {
        return *this;
    }

    // Chama o operador de atribuição da classe base (FlappyBus)
    static_cast<FlappyBus&>(*this) = other;

    this->propulsionType = other.propulsionType;

    return *this;
}

bool SpaceBus::operator==(const SpaceBus& other) const {
    if (this == &other) {
        return true;
    }

    // Compara a parte da classe base (FlappyBus)
    if (static_cast<const FlappyBus&>(*this) != static_cast<const FlappyBus&>(other)) {
        return false;
    }

    return this->propulsionType == other.propulsionType;
}

bool SpaceBus::operator!=(const SpaceBus& other) const {
    return !(*this == other);
}

bool SpaceBus::operator!() const {
    // Usa a negação da classe base (FlappyBus)
    return !static_cast<const FlappyBus&>(*this);
}

std::ostream& operator<<(std::ostream& os, const SpaceBus& spaceBus) {
    // Usa a sobrecarga da classe base (FlappyBus)
    os << static_cast<const FlappyBus&>(spaceBus);

    os << "Tipo de Propulsao: " << spaceBus.propulsionType << "\n";

    return os;
}

// Carregamento de arquivos
bool SpaceBus::isNumeric(const std::string& str) {
    return !str.empty() && std::all_of(str.begin(), str.end(), [](char c) {
        return std::isdigit(c) || c == '.' || c == '-';
    });
}

bool SpaceBus::loadVariablesFromFile(const std::string& filename) {
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

bool SpaceBus::processVariables(const std::map<std::string, double>& numericVariables, const std::map<std::string, std::string>& stringVariables) {
   if (numericVariables.find("initialPosition") != numericVariables.end())
        setPosition(numericVariables.at("initialPosition"));

    if (numericVariables.find("initialVelocity") != numericVariables.end())
        setVelocity(numericVariables.at("initialVelocity"));

    if (stringVariables.find("name") != stringVariables.end())
        setPlayerName(stringVariables.at("name"));

    if (stringVariables.find("propulsionType") != stringVariables.end())
        this->propulsionType = stringVariables.at("propulsionType");

    return true;
}

bool SpaceBus::saveVariablesToFile(const std::string& filename) const {
    std::ofstream outputFile(filename);
    if (!outputFile.is_open()) {
        std::cerr << "Error opening file for writing: " << filename << '\n';
        return false;
    }

    outputFile << "initialPosition = " << getPosition() << '\n';
    outputFile << "initialVelocity = " << getVelocity() << '\n';
    outputFile << "name = " << getPlayerName() << '\n';
    outputFile << "propulsionType = " << this->propulsionType << '\n';

    outputFile.close();

    return true;
}



std::string SpaceBus::getPropulsionType() const {
    return propulsionType;
}

void SpaceBus::setPropulsionType(const std::string& propulsionType) {
    this->propulsionType = propulsionType;
}

bool SpaceBus::isHatchOpen() const {
    return hatchOpen;
}

void SpaceBus::setHatchOpen(bool hatchOpen) {
    this->hatchOpen = hatchOpen;
}

double SpaceBus::getEnvironmentalTemperature() const {
    return environmentalTemperature;
}

void SpaceBus::setEnvironmentalTemperature(double temperature) {
    this->environmentalTemperature = temperature;
}

double SpaceBus::getEnvironmentalPressure() const {
    return environmentalPressure;
}

void SpaceBus::setEnvironmentalPressure(double pressure) {
    this->environmentalPressure = pressure;
}

double SpaceBus::getEnvironmentalOxygenLevel() const {
    return environmentalOxygenLevel;
}

void SpaceBus::setEnvironmentalOxygenLevel(double oxygenLevel) {
    this->environmentalOxygenLevel = oxygenLevel;
}

std::string SpaceBus::getDestination() const {
    return destination;
}

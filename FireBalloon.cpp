#include "FireBalloon.h"

FireBalloon::FireBalloon(): HotAirBalloon(),  FireControl() {}

FireBalloon::FireBalloon(int initialPosition, double initialVelocity): HotAirBalloon(initialPosition, initialVelocity), FireControl() {}

FireBalloon::FireBalloon(const FireBalloon& other): HotAirBalloon(other), FireControl(other) {}

FireBalloon::~FireBalloon() {}

void FireBalloon::ignite() {
    // Implementação específica para iniciar o fogo (herdado de FireControl)
    std::cout << "FireBalloon igniting fire!" << std::endl;
    isOnFire = true;
}

void FireBalloon::extinguish() {
    // Implementação específica para apagar o fogo (herdado de FireControl)
    std::cout << "FireBalloon extinguishing fire!" << std::endl;
    isOnFire = false;
}

std::string FireBalloon::getDescription() const {
    // Descrição específica para FireBalloon
    return isOnFire ? "FireBalloon with fire control (On Fire)" : "FireBalloon with fire control (Not On Fire)";
}

void FireBalloon::spreadFire() {
    if (isOnFire) {
        std::cout << "FireBalloon spreading fire!" << std::endl;
    } else {
        std::cout << "FireBalloon is not on fire. Ignite the fire first!" << std::endl;
    }
}

// Sobrecarga dos operadores
FireBalloon& FireBalloon::operator=(const FireBalloon& other) {
    if (this == &other) {
        return *this;
    }

    // Chama o operador de atribuição da classe base (HotAirBalloon)
    static_cast<HotAirBalloon&>(*this) = other;

    // Adiciona atributos específicos de FireBalloon
    this->isOnFire = other.isOnFire;

    return *this;
}

bool FireBalloon::operator==(const FireBalloon& other) const {
    if (this == &other) {
        return true;
    }

    // Compara a parte da classe base (HotAirBalloon)
    if (static_cast<const HotAirBalloon&>(*this) != static_cast<const HotAirBalloon&>(other)) {
        return false;
    }

    return this->isOnFire == other.isOnFire;
}

bool FireBalloon::operator!=(const FireBalloon& other) const {
    return !(*this == other);
}

bool FireBalloon::operator!() const {
    // Usa a negação da classe base (HotAirBalloon)
    return !static_cast<const HotAirBalloon&>(*this);
}

std::ostream& operator<<(std::ostream& os, const FireBalloon& fireBalloon) {
    // Usa a sobrecarga da classe base (HotAirBalloon)
    os << static_cast<const HotAirBalloon&>(fireBalloon);
    os << (fireBalloon.isOnFire ? "On Fire" : "Not On Fire") << "\n";

    return os;
}


// Carregamento de arquivos
bool FireBalloon::loadVariablesFromFile(const std::string& filename) {
    return HotAirBalloon::loadVariablesFromFile(filename);
}

bool FireBalloon::processVariables(const std::map<std::string, double>& numericVariables, const std::map<std::string, std::string>& stringVariables, const std::map<std::string, bool>&  boolVariables) {
    // Chama o método da classe base (HotAirBalloon)
    if (!HotAirBalloon::processVariables(numericVariables, stringVariables, boolVariables)) {
        return false;
    }

     if (boolVariables.find("isOnFire") != boolVariables.end())
        this->isOnFire = boolVariables.at("isOnFire");

    return true;
}

bool FireBalloon::saveVariablesToFile(const std::string& filename) const {
    std::ofstream outputFile(filename);
    if (!outputFile.is_open()) {
        std::cerr << "Error opening file for writing: " << filename << '\n';
        return false;
    }
   
    outputFile << "initialPosition = " << getPosition() << '\n';
    outputFile << "initialVelocity = " << getVelocity() << '\n';
    outputFile << "name = " << getPlayerName() << '\n';
    outputFile << "gasLevel = " << getGasLevel() << '\n';
    outputFile << "isOnFire = " << this->isOnFire << '\n';

    outputFile.close();

    return true;
}

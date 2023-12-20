#include "WaterBalloon.h"

WaterBalloon::WaterBalloon(): HotAirBalloon(), WaterControl(){}

WaterBalloon::WaterBalloon(int initialPosition, double initialVelocity): HotAirBalloon(initialPosition, initialVelocity), WaterControl() {}

WaterBalloon::WaterBalloon(const WaterBalloon& other): HotAirBalloon(other), WaterControl(other) {}

WaterBalloon::~WaterBalloon() {}

void WaterBalloon::fill() {
    // Implementação específica para encher o balão com água
    std::cout << "WaterBalloon filling with water!" << std::endl;
}

void WaterBalloon::release() {
    // Implementação específica para liberar água do balão
    std::cout << "WaterBalloon releasing water!" << std::endl;
}

std::string WaterBalloon::getDescription() const {
    // Descrição específica para WaterBalloon
    return "WaterBalloon with water control";
}


/* PatternType:
*   1 - Espiral
*   2 - Zigue-zague
*   3 - Aleatório
*/
void WaterBalloon::createWaterPatterns(int patternType, int intensity) {

    std::cout << "Creating water patterns with intensity " << intensity << "...\n";

    switch (patternType) {
        case 1: {
            std::cout << "Creating spiral water pattern.\n";
            for (int i = 0; i < intensity; ++i) {
                std::cout << "Spraying water in a spiral pattern: " << i << "\n";
            }
            break;
        }
        case 2: {
            std::cout << "Creating zigzag water pattern.\n";
            for (int i = 0; i < intensity; ++i) {
                std::cout << "Spraying water in a zigzag pattern: " << (i % 2 == 0 ? "left" : "right") << "\n";
            }
            break;
        }
        case 3: {
            std::cout << "Creating random water pattern.\n";
            srand(static_cast<unsigned int>(time(nullptr)));
            for (int i = 0; i < intensity; ++i) {
                int randomDirection = rand() % 4;  // 0: cima, 1: baixo, 2: esquerda, 3: direita
                std::cout << "Spraying water in a random direction: " << randomDirection << "\n";
            }
            break;
        }
        default:
            std::cout << "Unknown water pattern type.\n";
            break;
    }

}

// Sobrecarga dos operadores
WaterBalloon& WaterBalloon::operator=(const WaterBalloon& other) {
    if (this == &other) {
        return *this;
    }

    // Chama o operador de atribuição da classe base (HotAirBalloon)
    static_cast<HotAirBalloon&>(*this) = other;

    return *this;
}

bool WaterBalloon::operator==(const WaterBalloon& other) const {
    if (this == &other) {
        return true;
    }

    // Compara a parte da classe base (HotAirBalloon)
    return static_cast<const HotAirBalloon&>(*this) == static_cast<const HotAirBalloon&>(other);
}

bool WaterBalloon::operator!=(const WaterBalloon& other) const {
    return !(*this == other);
}

bool WaterBalloon::operator!() const {
    // Usa a negação da classe base (HotAirBalloon)
    return !static_cast<const HotAirBalloon&>(*this);
}

std::ostream& operator<<(std::ostream& os, const WaterBalloon& waterBalloon) {
    // Usa a sobrecarga da classe base (HotAirBalloon)
    os << static_cast<const HotAirBalloon&>(waterBalloon);

    return os;
}

// Carregamento de arquivos
bool WaterBalloon::loadVariablesFromFile(const std::string& filename) {
    return HotAirBalloon::loadVariablesFromFile(filename);
}

bool WaterBalloon::processVariables(const std::map<std::string, double>& numericVariables,const std::map<std::string, std::string>& stringVariables, const std::map<std::string, bool>& boolVariables) {
    return HotAirBalloon::processVariables(numericVariables, stringVariables, boolVariables);
}

bool WaterBalloon::saveVariablesToFile(const std::string& filename) const {
    return HotAirBalloon::saveVariablesToFile(filename);
}
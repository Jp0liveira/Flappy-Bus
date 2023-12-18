#include "HotAirBalloon.h"

HotAirBalloon::HotAirBalloon():  FloatingObstacle(){}

HotAirBalloon::HotAirBalloon(int initialPosition, double initialVelocity): FloatingObstacle(initialPosition, initialVelocity) {}

HotAirBalloon::HotAirBalloon(const HotAirBalloon& other): FloatingObstacle(other) {}

HotAirBalloon::~HotAirBalloon() {}

void HotAirBalloon::floatInAir() {
    // Implementação específica para flutuar no ar (herdado de FloatingObstacle)
    std::cout << "HotAirBalloon floating in the air!" << std::endl;
}

void HotAirBalloon::applyWindForce() {
    // Implementação específica para aplicar força de vento (herdado de FloatingObstacle)
    std::cout << "HotAirBalloon applying wind force!" << std::endl;
}



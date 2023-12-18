#include "FloatingObstacle.h"

FloatingObstacle::FloatingObstacle() : ObstacleCharacter() {
    ObstacleCharacter::obstacleType = ObstacleType::FLOATINGOBSTACLE;
}

FloatingObstacle::FloatingObstacle(int initialPosition, double initialVelocity)
    : ObstacleCharacter(initialPosition, initialVelocity, ObstacleType::FLOATINGOBSTACLE) {}

FloatingObstacle::FloatingObstacle(const FloatingObstacle& other): ObstacleCharacter(other) {}

FloatingObstacle::~FloatingObstacle() {}

void FloatingObstacle::collide() {
    // Implementação específica para colisões com obstáculos flutuantes
     std::cout << "FloatingObstacle collided!" << std::endl;
}

void FloatingObstacle::moveDown() {
    // Implementação específica para movimentação descendente de obstáculos flutuantes
     std::cout << "FloatingObstacle moving down!" << std::endl;
}
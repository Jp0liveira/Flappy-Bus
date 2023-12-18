#include "ObstacleCharacter.h"
ObstacleCharacter::ObstacleCharacter(): FlappyBus(), obstacleType(BLOCK){}

ObstacleCharacter::ObstacleCharacter(int initialPosition, double initialVelocity, ObstacleType obstacleType): FlappyBus(initialPosition, initialVelocity, "Obstacle"), obstacleType(obstacleType) {}

ObstacleCharacter::ObstacleCharacter(const ObstacleCharacter& other): FlappyBus(other), obstacleType(other.obstacleType) {}

ObstacleCharacter::~ObstacleCharacter() {}

std::string ObstacleCharacter::getObstacleTypeName() const {
    std::cout << "Obstacle Type: ";
    switch (obstacleType) {
        case BLOCK:
            return "Block";
        case HOUSE:
            return "House";
        case TREE:
            return "Tree";
        case ROCK:
            return "Rock";
        case CLOUD:
            return "Cloud";
        case MOUNTAIN:
            return "Mountain";
        case BRIDGE:
            return "Bridge";
        case BUSH:
            return "Bush";
        case FENCE:
            return "Fence";
        case TOWER:
            return "Tower";
        case FLOATINGOBSTACLE:
            return "FloatingObstacle";
        default:
            return "Unknown";
    }
}

#include "BusObstacle.h"
#include <iostream>

BusObstacle::BusObstacle() : position(0), obstacleType("onibus"), obstacleHeight(0) {}

BusObstacle::BusObstacle(int initialPosition, const std::string& type, int height)
    : position(initialPosition), obstacleType(type), obstacleHeight(height) {}

int BusObstacle::getPosition() const {
    return position;
}

std::string BusObstacle::getObstacleType() const {
    return obstacleType;
}

int BusObstacle::getObstacleHeight() const {
    return obstacleHeight;
}

void BusObstacle::move(int newPosition) {
    position = newPosition;
}

void BusObstacle::displayInfo() const {
    std::cout << "Obstacle Type: " << obstacleType << std::endl;
    std::cout << "Position: " << position << std::endl;
    std::cout << "Height: " << obstacleHeight << std::endl;
}

void BusObstacle::checkCollision(const BusObstacle& obstacle) const {
    if (position >= obstacle.getObstacleHeight() && position <= obstacle.getObstacleHeight() + 5 &&
        obstacle.getPosition() <= 10) {
        std::cout << "Collision with " << obstacle.getObstacleType() << " at position " << obstacle.getPosition() << std::endl;
    }
}

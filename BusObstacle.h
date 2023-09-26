#pragma once
#include <string>

class BusObstacle {
private:
    int position;
    const std::string obstacleType;
    const int obstacleHeight;

public:
    BusObstacle();
    BusObstacle(int initialPosition, const std::string& type, int height);
    
    int getPosition() const;
    std::string getObstacleType() const;
    int getObstacleHeight() const;
    
    void move(int newPosition);
    void displayInfo() const;
    void checkCollision(const BusObstacle& obstacle) const;
};

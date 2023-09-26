#pragma once

#include "FlappyBus.h"
#include "BusObstacle.h"
#include "ScoreManager.h"

class GameFlappyBus : public FlappyBus, public BusObstacle, public ScoreManager {

public:
    GameFlappyBus();
    GameFlappyBus(const FlappyBus& player, const BusObstacle& obstacle, const ScoreManager& score);
    ~GameFlappyBus();
    void playGame();

private:
    FlappyBus player;
    BusObstacle obstacle;
    ScoreManager score;

};

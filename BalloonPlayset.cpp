#include "BalloonPlayset.h"

BalloonPlayset::BalloonPlayset() {}

BalloonPlayset::~BalloonPlayset() {
    for (auto balloon : balloons) {
        delete balloon;
    }
}

void BalloonPlayset::addBalloon(HotAirBalloon* balloon) {
    balloons.push_back(balloon);
}

void BalloonPlayset::playWithBalloons() {
    for (auto balloon : balloons) {
        
        balloon->floatInAir();
        balloon->applyWindForce();

        // verifica se realmente é um tipo FireBalloon
        FireBalloon* fireBalloon = dynamic_cast<FireBalloon*>(balloon);
        if (fireBalloon) {
            fireBalloon->ignite();
        }

        // verifica se realmente é um tipo WaterBalloon
        WaterBalloon* waterBalloon = dynamic_cast<WaterBalloon*>(balloon);
        if (waterBalloon) {
            waterBalloon->fill();
        }
    }
}

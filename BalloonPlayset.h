#pragma once
#include "HotAirBalloon.h"
#include <vector>

class BalloonPlayset {
    public:
        BalloonPlayset();
        ~BalloonPlayset();

        void addBalloon(HotAirBalloon* balloon);
        void playWithBalloons();

    private:
        std::vector<HotAirBalloon*> balloons;
};

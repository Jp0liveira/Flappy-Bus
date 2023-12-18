#pragma once
#include "FloatingObstacle.h"

class HotAirBalloon : public FloatingObstacle {

    public:
        HotAirBalloon();
        HotAirBalloon(int initialPosition, double initialVelocity);
        HotAirBalloon(const HotAirBalloon& other);
        virtual ~HotAirBalloon();

        // Métodos virtuais puros específicos
        virtual void heatUp() = 0;  // Método para aquecer o balão de ar quente
        virtual void coolDown() = 0;  // Método para resfriar o balão de ar quente

        // Implementações concretas para métodos virtuais herdados
        void floatInAir() override;
        void applyWindForce() override;
        
};

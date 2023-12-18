#pragma once
#include "ObstacleCharacter.h"

class FloatingObstacle : public ObstacleCharacter {
    public:
        FloatingObstacle(); 
        FloatingObstacle(int initialPosition, double initialVelocity);
        FloatingObstacle(const FloatingObstacle& other);
        virtual ~FloatingObstacle(); 
        
        void collide() override;
        void moveDown() override;

        // // // Métodos virtuais puros
        virtual void floatInAir() = 0;   // Método específico para obstáculos flutuantes
        virtual void applyWindForce() = 0;  // Método para aplicar força de vento

};
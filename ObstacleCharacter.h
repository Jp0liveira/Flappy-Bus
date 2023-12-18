#pragma once
#include "FlappyBus.h"

enum ObstacleType {
    BLOCK,
    HOUSE,
    TREE,
    ROCK,
    CLOUD,
    MOUNTAIN,
    BRIDGE,
    BUSH,
    FENCE,
    TOWER,
    FLOATINGOBSTACLE,
};

class ObstacleCharacter : public FlappyBus {

    public:
        ObstacleCharacter(); 
        ObstacleCharacter(int initialPosition, double initialVelocity, ObstacleType obstacleType);
        ObstacleCharacter(const ObstacleCharacter& other); 
        virtual ~ObstacleCharacter();

        // // Métodos puros
        virtual void collide() = 0;   // Método chamado quando ocorre uma colisão
        virtual void moveDown() = 0;  // Método chamado para movimentação descendente do obstáculo

        std::string getObstacleTypeName() const;  // Retorna o nome legível do tipo de obstáculo

    protected:
        ObstacleType obstacleType;
};

#include <iostream>
#include <algorithm>
#include "main_includes.h"

int main() {
   
    FlappyBus flappyBus(5, 2, "Joao"); 

    // Adicionando obstáculos ao FlappyBus
    flappyBus.addObstaculoEmMovimento(7, 2, 1, 1);
    flappyBus.addObstaculoEstatico(10, 2, 4, 3); 
    
    flappyBus.jump();
    
    if (flappyBus.getHadCollision()) {  
        std::cout << "FlappyBus colidiu com um obstaculo!" << std::endl;
    } else {
        std::cout << "FlappyBus nao colidiu com nenhum obstaculo." << std::endl;
    }

    return 0;

}

#include <iostream>
#include "main_includes.h"

int main() {
   
    // Criando instâncias de balões
    HotAirBalloon* hotAirBalloon = new HotAirBalloon();
    FireBalloon* fireBalloon = new FireBalloon(1, 10.0);
    WaterBalloon* waterBalloon = new WaterBalloon(2, 8.0);

    // Criando uma instância de BalloonPlayset
    BalloonPlayset balloonPlayset;

    // Adicionando balões ao conjunto de obstaculos
    balloonPlayset.addBalloon(hotAirBalloon);
    balloonPlayset.addBalloon(fireBalloon);
    balloonPlayset.addBalloon(waterBalloon);

    // Simulando os obstaculos com os balões
    balloonPlayset.playWithBalloons();

    // Liberando a memória alocada
    delete hotAirBalloon;
    delete fireBalloon;
    delete waterBalloon;
    
    return 0;

}

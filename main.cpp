#include <iostream>
#include <algorithm>
#include "main_includes.h"

int main() {
   // Cria um PowerUp usando o construtor padrão
    PowerUp powerUp1;
    
    // Cria outro PowerUp usando o construtor com parâmetros
    PowerUp powerUp2("SpeedBoost", 500);

    // Cria um terceiro PowerUp usando o construtor de cópia
    PowerUp powerUp3 = powerUp2;

    // Exibe informações sobre os PowerUps
    std::cout << "PowerUp 1: Nome=" << powerUp1.getName() << ", Duracao=" << powerUp1.getDuration() << std::endl;
    std::cout << "PowerUp 2: Nome=" << powerUp2.getName() << ", Durcao=" << powerUp2.getDuration() << std::endl;
    std::cout << "PowerUp 3: Nome=" << powerUp3.getName() << ", Duracao=" << powerUp3.getDuration() << std::endl;

    return 0;

}

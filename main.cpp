#include <iostream>
#include "main_includes.h"

int main() {

    GameManager game1;
    GameManager game2(5, 9.8);
    
    game2.startGame();

    return 0;
}

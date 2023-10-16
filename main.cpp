#include <iostream>
#include "main_includes.h"

int main() {
    GameManager gameManager(3, 9.8);
    GameManager* copiedGameManagerPtr = new GameManager(gameManager);

    // Alocar memória para o histórico de jogos
    copiedGameManagerPtr->alocarHist();

    // Criar um novo objeto GameManager para ser registrado no histórico
    GameManager gameToRegister(2, 9.8);

    // Cadastrar o objeto no histórico
    copiedGameManagerPtr->cadastrarRegInHist(gameToRegister);

    // Mostrar a quantidade de jogos no histórico
    copiedGameManagerPtr->printGameCount();

    // Libere a memória alocada dinamicamente
    delete copiedGameManagerPtr;
    
    return 0;
}

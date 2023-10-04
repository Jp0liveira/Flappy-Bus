#include "GameManager.h"

// Inicialização de atributos estáticos
int GameManager::gameCount = 0;
double GameManager::gravity = 9.8;

// Inicialização de array const static
const int GameManager::levelScores[maxLevels] = {10, 20, 30, 40, 50};

GameManager::GameManager() {
     for (int i = 0; i < maxPlayers; ++i) {
        playerScores[i] = 0;
    }
}

GameManager::GameManager(int initialGameCount, double initialGravity) {
    gameCount = initialGameCount;
    gravity = initialGravity;
     for (int i = 0; i < maxPlayers; ++i) {
        playerScores[i] = 0;
    }
}

GameManager::GameManager(const GameManager& c_gameManager) {
    this->gameCount = c_gameManager.gameCount;
    this->gravity = c_gameManager.gravity;
     for (int i = 0; i < maxPlayers; ++i) {
        playerScores[i] = c_gameManager.playerScores[i];
    }
}

GameManager::~GameManager(){}


void GameManager::startGame() {
    printWelcomeMessage();

    FlappyBus player;
    int level = 0;

    while (level < maxLevels) {
        std::cout << "Nivel " << level + 1 << ": Pontuacao maxima = " << levelScores[level] << std::endl;
        player.jump();
        applyGravity(player);

        if (player.getScore() >= levelScores[level]) {
            std::cout << "Voce avancou para o proximo nivel!" << std::endl;
            level++;
        }

        std::cout << "Pontuacao atual: " << player.getScore() << std::endl;
    }

    std::cout << "Parabens! Você concluiu todos os niveis." << std::endl;
}

void GameManager::printGameCount() {
    std::cout << "Quantidade de jogos iniciados: " << gameCount << std::endl;
}

void GameManager::applyGravity(FlappyBus& player) {
    player.setVelocity(player.getVelocity() + gravity);
}

#include "GameManager.h"

// Inicialização de atributos estáticos
int GameManager::gameCount = 0;
double GameManager::gravity = 9.8;

// Inicialização de array const static
const int GameManager::levelScores[maxLevels] = {5, 10, 15, 20, 30};

GameManager::GameManager(): winHistory(nullptr), winHistorySize(0), winCount(0) {
     for (int i = 0; i < maxPlayers; ++i) {
        playerScores[i] = 0;
    }
}

GameManager::GameManager(int initialGameCount, double initialGravity): winHistory(nullptr), winHistorySize(0), winCount(0) {
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

    // Copiar o histórico de vitórias
    this->winHistorySize = c_gameManager.winHistorySize;
    this->winCount = c_gameManager.winCount;
    this->winHistory = new std::string[this->winHistorySize];
    for (int i = 0; i < winCount; ++i) {
        this->winHistory[i] = c_gameManager.winHistory[i];
    }
}

GameManager::~GameManager(){
     delete[] winHistory;  // Libere a memória alocada para o histórico de vitórias
}


void GameManager::startGame() {
    printWelcomeMessage();

    FlappyBus player(5, 0.5, "joao paulo");
    int level = 0;

    while (level < maxLevels) {
        std::cout << "Nivel " << level + 1 << ": Pontuacao maxima = " << levelScores[level] << std::endl;
        player.jump();
        applyGravity(player);

        if (player.getScore() >= levelScores[level]) {
            std::cout << "Voce avancou para o proximo nivel!" << std::endl;
            level++;
            this->registerWin(player.getPlayerName());
        }

        std::cout << "Pontuacao atual: " << player.getScore() << std::endl;
    }

    std::cout << "Parabens! Voce concluiu todos os niveis." << std::endl;
    this->displayWinHistory();
}

void GameManager::printGameCount() {
    std::cout << "Quantidade de jogos iniciados: " << gameCount << std::endl;
}

void GameManager::applyGravity(FlappyBus& player) {
    player.setVelocity(player.getVelocity() + gravity);
}

void GameManager::registerWin(const std::string& playerName) {
    if (winCount >= winHistorySize) {
        allocateMemory(winHistorySize + 1);
    }
    winHistory[winCount++] = playerName;
}

void GameManager::displayWinHistory() const {
    std::cout << "Historico de Vitorias:\n";
    for (int i = 0; i < winCount; ++i) {
        std::cout << "Vitoria " << i + 1 << ": " << winHistory[i] << std::endl;
    }
}

void GameManager::allocateMemory(int newSize) {
    std::string* newWinHistory = new std::string[newSize];
    for (int i = 0; i < winCount; ++i) {
        newWinHistory[i] = winHistory[i];
    }
    delete[] winHistory;
    winHistory = newWinHistory;
    winHistorySize = newSize;
}

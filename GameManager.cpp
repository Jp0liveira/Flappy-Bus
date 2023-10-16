#include "GameManager.h"

// Inicialização de atributos estáticos
int GameManager::gameCount = 0;
double GameManager::gravity = 9.8;

// Inicialização de array const static
const int GameManager::levelScores[maxLevels] = {5, 10, 15, 20, 30};

GameManager::GameManager() : MAXGAMESHISTORY(10) {
    history = nullptr; // Inicializando o ponteiro como nulo
    intPointer = new int; // Aloca memória para o ponteiro intPointer
    doublePointer = new double; // Aloca memória para o ponteiro doublePointer
    for (int i = 0; i < maxPlayers; ++i) {
        playerScores[i] = 0;
    }
}

GameManager::GameManager(int initialGameCount, double initialGravity) : MAXGAMESHISTORY(10) {
    gameCount = initialGameCount;
    gravity = initialGravity;
    history = nullptr; // Inicializando o ponteiro como nulo
    intPointer = new int; // Aloca memória para o ponteiro intPointer
    doublePointer = new double; // Aloca memória para o ponteiro doublePointer
    for (int i = 0; i < maxPlayers; ++i) {
        playerScores[i] = 0;
    }
}

GameManager::GameManager(const GameManager& c_gameManager) : MAXGAMESHISTORY(10) {
    this->gameCount = c_gameManager.gameCount;
    this->gravity = c_gameManager.gravity;
    this->history = nullptr; // Inicializando o ponteiro como nulo
    this->copyHistory(c_gameManager);
    for (int i = 0; i < maxPlayers; ++i) {
        playerScores[i] = c_gameManager.playerScores[i];
    }
}

GameManager::~GameManager() {
    delete[] history; // Desaloca o histórico de jogos
    delete intPointer; // Desaloca o intPointer
    delete doublePointer; // Desaloca o doublePointer

}

void GameManager::startGame() {
    printWelcomeMessage();

    FlappyBus player;
    int level = 0;

    while (level < maxLevels) {
        std::cout << "Nivel " << level + 1 << ": Pontuacao maxima = " << levelScores[level] << std::endl;
        player.jump();
        applyGravity(player);
        bool collide = player.didCollide(player.getPosition(), player.getVelocity());
        if (!collide) {
            if (player.getScore() >= levelScores[level]) {
                std::cout << "Voce avancou para o proximo nivel!" << std::endl;
                level++;
            }
        }

        std::cout << "Pontuacao atual: " << player.getScore() << std::endl;
    }

    std::cout << "Parabens! Voce concluiu todos os niveis." << std::endl;
}

void GameManager::printGameCount() {
    std::cout << "Quantidade de jogos iniciados: " << gameCount << std::endl;
}

void GameManager::applyGravity(FlappyBus& player) {
    player.setVelocity(player.getVelocity() + gravity);
}

// Método para alocar memória para o histórico de jogos (history)
void GameManager::alocarHist() {
    if (!history) {
        history = new GameManager[MAXGAMESHISTORY];
    }
}

// Método para cadastrar um registro no histórico de jogos
void GameManager::cadastrarRegInHist(const GameManager& game) {
    int emptySlot = findEmptySlot();
    if (emptySlot >= 0) {
        // Copia os dados do jogo fornecido para o slot vazio no histórico
        history[emptySlot].gameCount = game.gameCount;
        history[emptySlot].gravity = game.gravity;
        history[emptySlot].copyHistory(game);
        for (int i = 0; i < maxPlayers; ++i) {
            playerScores[i] = game.playerScores[i];
        }
        gameCount++;
    }
}

// Método para encontrar um slot vazio no histórico
int GameManager::findEmptySlot() const {
    for (int i = 0; i < MAXGAMESHISTORY; i++) {
        if (history[i].gameCount == 0) {
            return i;
        }
    }
    return -1; // Retorna -1 se nenhum slot vazio for encontrado
}

// Método para copiar o histórico de jogos (para futuras referências)
void GameManager::copyHistory(const GameManager& game) {
    if (!history) {
        return;
    }
    for (int i = 0; i < MAXGAMESHISTORY; i++) {
        history[i].gameCount = game.gameCount;
        history[i].gravity = game.gravity;
        for (int j = 0; j < maxPlayers; ++j) {
            playerScores[j] = game.playerScores[j];
        }
    }
}

void GameManager::allocateMemoryForPointers() {
    // Aloca memória para o ponteiro intPointer
    intPointer = new int;
    if (!intPointer) {
        std::cout << "Falha na alocacao de memoria para intPointer." << std::endl;
    }else{
        std::cout << "Sucesso na alocacao de memoria para intPointer." << std::endl;
    }

    // Aloca memória para o ponteiro doublePointer
    doublePointer = new double;
    if (!doublePointer) {
        std::cout << "Falha na alocacao de memoria para doublePointer." << std::endl;
    }else{
         std::cout << "Sucesso na alocacao de memoria para doublePointer." << std::endl;
    }
}

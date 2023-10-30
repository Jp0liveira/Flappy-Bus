#include "GameManager.h"

// Inicialização de atributos estáticos
int GameManager::gameCount = 0;
double GameManager::gravity = 9.8;
const int GameManager::levelScores[maxLevels] = {5, 10, 15, 20, 30};

GameManager::GameManager(): winHistory(nullptr), winHistorySize(0), winCount(0) {
    playersInGame.reserve(maxPlayers);
     for (int i = 0; i < maxPlayers; ++i) {
        playerScores[i] = 0;
    }
     
}

GameManager::GameManager(int initialGameCount, double initialGravity): winHistory(nullptr), winHistorySize(0), winCount(0) {
    gameCount = initialGameCount;
    gravity = initialGravity;
    playersInGame.reserve(maxPlayers);
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

    // Copiar jogadores em jogo, alocando memória para novos objetos FlappyBus
    for (const FlappyBus* player : c_gameManager.playersInGame) {   
        FlappyBus* newPlayer = new FlappyBus(*player);
        playersInGame.push_back(newPlayer);
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
     for (FlappyBus* player : playersInGame) {   // Liberar a memória alocada para jogadores em jogo
        delete player;
    }
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

// Uso do vector
void GameManager::addPlayerToGame(FlappyBus* player) {
    if (playersInGame.size() < maxPlayers) {
        playersInGame.push_back(player);
    } else {
        std::cout << "Nao e possivel adicionar mais jogadores. O limite foi atingido." << std::endl;
    }
}

void GameManager::removePlayerFromGame(const std::string& playerName) {
    for (auto it = playersInGame.begin(); it != playersInGame.end(); ++it) {
        if ((*it)->getPlayerName() == playerName) {
            delete *it; // Liberar a memória alocada para o jogador removido
            playersInGame.erase(it);
            return;
        }
    }
    std::cout << "Jogador não encontrado no jogo." << std::endl;
}

void GameManager::displayPlayersInGame() const {
    std::cout << "Jogadores em jogo:" << std::endl;
    for (const FlappyBus* player : playersInGame) {
        std::cout << *player << std::endl;
    }
}

// Alocação de memória
void GameManager::registerWin(const std::string& playerName) {
    if (winCount >= winHistorySize) {
        allocateMemory(winHistorySize + 1);
    }
    winHistory[winCount++] = playerName;

     // Atualize a pontuação do jogador correspondente
    int levelIndex = (winCount - 1) >= maxLevels ? (maxLevels - 1) : (winCount - 1);
    for (int i = 0; i < maxPlayers; ++i) {
        if (playerScores[i] == 0) {
            // Se a pontuação do jogador estiver vazia (0), atribua a pontuação
            playerScores[i] = levelScores[levelIndex];
            break;
        }
    }

    // Verifique se não ultrapassou o limite de 10 registros
    if (winCount > maxPlayers) {
        std::cout << "Atingido o limite de registros. Nao e possivel registrar mais vitorias." << std::endl;
        // Reduza winCount para 10
        winCount = maxPlayers;
    }
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
    
// Sobrecarga dos Operadores
GameManager& GameManager::operator=(const GameManager& other) {
    if (this == &other) {
        return *this;
    }

    // Copiar atributos não estáticos
    this->gameCount = other.gameCount;
    this->gravity = other.gravity;

    // Copiar histórico de vitórias
    this->winHistorySize = other.winHistorySize;
    this->winCount = other.winCount;
    delete[] winHistory;
    this->winHistory = new std::string[this->winHistorySize];
    for (int i = 0; i < winCount; ++i) {
        this->winHistory[i] = other.winHistory[i];
    }

    // Copiar atributos de jogadores
    for (int i = 0; i < maxPlayers; ++i) {
        this->playerScores[i] = other.playerScores[i];
    }

    return *this;
}

bool GameManager::operator==(const GameManager& other) const {
    if (this == &other) {
        return true;
    }

    // Comparar atributos não estáticos
    if (this->gameCount != other.gameCount || this->gravity != other.gravity) {
        return false;
    }

    // Comparar histórico de vitórias
    if (this->winCount != other.winCount) {
        return false;
    }
    for (int i = 0; i < winCount; ++i) {
        if (this->winHistory[i] != other.winHistory[i]) {
            return false;
        }
    }

    // Comparar atributos de jogadores
    for (int i = 0; i < maxPlayers; ++i) {
        if (this->playerScores[i] != other.playerScores[i]) {
            return false;
        }
    }

    return true;
}

bool GameManager::operator!=(const GameManager& other) const {
    return !(*this == other);
}

bool GameManager::operator!() const {
    return winCount == 0;
}

std::ostream& operator<<(std::ostream& os, const GameManager& gameManager) {
    
    os << "Quantidade de jogos iniciados: " << gameManager.gameCount << std::endl;
    os << "Gravidade: " << gameManager.gravity << std::endl;
    os << "Historico de Vitorias:" << std::endl;
    for (int i = 0; i < gameManager.winCount; ++i) {
        os << "Vitoria " << i + 1 << ": " << gameManager.winHistory[i] << std::endl;
    }
    os << "Historico de niveis:" << std::endl;
    for (int i = 0; i < gameManager.maxPlayers; ++i) {
         if(gameManager.playerScores[i] == 0){
           break;
        }
        os << "Nivel " << i + 1 << " zerado com: " << gameManager.playerScores[i] << std::endl;
    }
    return os;
}

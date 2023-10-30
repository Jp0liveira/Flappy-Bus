#include "ScoreManager.h"

ScoreManager::ScoreManager() : score(0), MAXSCORE(100), scoreHistory(nullptr), historySize(0), historyCount(0) {}

ScoreManager::ScoreManager(int max, int historySize) : score(0), MAXSCORE(max),  scoreHistory(new int[historySize]), historySize(historySize), historyCount(0) {}

ScoreManager::ScoreManager(const ScoreManager &c_score): MAXSCORE(c_score.MAXSCORE), scoreHistory(new int[c_score.historySize]), historySize(c_score.historySize), historyCount(c_score.historyCount){
    this->score = c_score.score;
    for (int i = 0; i < historyCount; ++i) {
        this->scoreHistory[i] = c_score.scoreHistory[i];
    }
    
}

ScoreManager::~ScoreManager(){
      delete[] scoreHistory;
}

int ScoreManager::getCurrentScore() const {
    return score;
}

int ScoreManager::getMaxScore() const {
    return MAXSCORE;
}

int ScoreManager::increaseScore() {
    if (!isMaxScoreReached()) {
        recordScore(score + 1);  // Registro de pontuação no histórico
        scoreDate.setCurrentDate(); // Define a data e hora atual
        return score++;
    }
    return 0;
}

void ScoreManager::displayScoreData() const {
    std::cout << "Score Atual: " << score << std::endl;
    std::cout << "Pontuacao Maxima: " << MAXSCORE << std::endl;
    std::cout << "Data e Hora do Registro: ";
    scoreDate.print(); // Exibe a data e hora do registro
}

bool ScoreManager::isMaxScoreReached() const {
    return score >= MAXSCORE;
}

//Alocação de memória
void ScoreManager::recordScore(int newScore) {
    if (historyCount >= historySize) {
        int newHistorySize = historySize * 2;
        int* newScoreHistory = new int[newHistorySize];
        for (int i = 0; i < historyCount; ++i) {
            newScoreHistory[i] = scoreHistory[i];
        }

        delete[] scoreHistory;
        scoreHistory = newScoreHistory;
        historySize = newHistorySize;
    }
    scoreHistory[historyCount++] = newScore;
}

// Sobrecarga dos Operadores
ScoreManager& ScoreManager::operator=(const ScoreManager& other) {
    if (this == &other) {
        return *this;
    }

    this->score = other.score;
    return *this;
}

bool ScoreManager::operator==(const ScoreManager& other) const {
    if (this == &other) {
        return true;
    }

    return this->score == other.score;
}

bool ScoreManager::operator!=(const ScoreManager& other) const {
    return !(*this == other);
}

bool ScoreManager::operator!() const {
    return score == 0;
}

std::ostream& operator<<(std::ostream& os, const ScoreManager& scoreManager) {
    os << "Score Atual: " << scoreManager.score << std::endl;
    os << "Pontuacao Maxima: " << scoreManager.MAXSCORE << std::endl;
    return os;
}
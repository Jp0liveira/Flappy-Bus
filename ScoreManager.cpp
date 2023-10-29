#include "ScoreManager.h"

ScoreManager::ScoreManager() : score(0), MAXSCORE(100) {}

ScoreManager::ScoreManager(int max) : score(0), MAXSCORE(max) {}

ScoreManager::ScoreManager(const ScoreManager &c_score): MAXSCORE(c_score.MAXSCORE){
    this->score = c_score.score;
}

ScoreManager::~ScoreManager(){}

int ScoreManager::getCurrentScore() const {
    return score;
}

int ScoreManager::getMaxScore() const {
    return MAXSCORE;
}

int ScoreManager::increaseScore() {
    if (!isMaxScoreReached()) {
         return score++;
    }
    return 0;
}

bool ScoreManager::isMaxScoreReached() const {
    return score >= MAXSCORE;
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
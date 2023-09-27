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

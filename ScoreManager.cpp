#include "ScoreManager.h"

ScoreManager::ScoreManager() : score(0), maxScore(100) {}

ScoreManager::ScoreManager(int max) : score(0), maxScore(max) {}

int ScoreManager::getCurrentScore() const {
    return score;
}

int ScoreManager::getMaxScore() const {
    return maxScore;
}

void ScoreManager::increaseScore() {
    if (!isMaxScoreReached()) {
        score++;
    }
}

bool ScoreManager::isMaxScoreReached() const {
    return score >= maxScore;
}

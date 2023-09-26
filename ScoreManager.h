#pragma once

class ScoreManager {
private:
    int score;
    const int maxScore;

public:
    ScoreManager();
    ScoreManager(int max);

    int getCurrentScore() const;
    int getMaxScore() const;
    
    void increaseScore();
    bool isMaxScoreReached() const;
};

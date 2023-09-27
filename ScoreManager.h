#pragma once

class ScoreManager {

    public:
        ScoreManager();
        ScoreManager(int max);
        ScoreManager(const ScoreManager&);
        ~ScoreManager();

        int getCurrentScore() const;
        int getMaxScore() const;
        
        int increaseScore();
        bool isMaxScoreReached() const;

    private:
        int score;
        const int MAXSCORE;

};

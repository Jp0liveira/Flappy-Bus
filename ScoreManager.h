#pragma once

class ScoreManager {
        friend std::ostream& operator<<(std::ostream& os, const ScoreManager& scoreManager);
    public:
        ScoreManager();
        ScoreManager(int max);
        ScoreManager(const ScoreManager&);
        ~ScoreManager();

        int getCurrentScore() const;
        int getMaxScore() const;
        
        int increaseScore();
        bool isMaxScoreReached() const;

        // Sobrecargas dos operadores
        ScoreManager& operator=(const ScoreManager& other);
        bool operator==(const ScoreManager& other) const;
        bool operator!=(const ScoreManager& other) const;
        bool operator!() const;

    private:
        int score;
        const int MAXSCORE;

};

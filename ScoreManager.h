#pragma once
#include "Data.h"
class ScoreManager {
        friend std::ostream& operator<<(std::ostream& os, const ScoreManager& scoreManager);
    public:
        ScoreManager();
        ScoreManager(int max, int historySize);
        ScoreManager(const ScoreManager&);
        ~ScoreManager();

        int getCurrentScore() const;
        int getMaxScore() const;

        int getHistoryCount() const {return historyCount;}
        const int* getScoreHistory() const {return scoreHistory;}

        int increaseScore();
        bool isMaxScoreReached() const;

        // Função para registrar uma pontuação no histórico
        void recordScore(int score);

        // Sobrecargas dos operadores
        ScoreManager& operator=(const ScoreManager& other);
        bool operator==(const ScoreManager& other) const;
        bool operator!=(const ScoreManager& other) const;
        bool operator!() const;

        void displayScoreData() const;

    private:
        int score;
        const int MAXSCORE;

        // Histórico de pontuação
        int* scoreHistory;  
        int historySize;   
        int historyCount;

        Data scoreDate;

};

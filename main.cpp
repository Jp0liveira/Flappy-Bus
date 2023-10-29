#include <iostream>
#include "main_includes.h"

int main() {

    ScoreManager score1;
    ScoreManager score2(200);

    std::cout << "Score 1:\n" << score1 << std::endl;
    std::cout << "Score 2:\n" << score2 << std::endl;

    // Atribuição e comparação
    score1 = score2;
    std::cout << "Score 1 apos atribuicao:\n" << score1 << std::endl;

    if (score1 == score2) {
        std::cout << "Score 1 e igual a Score 2.\n";
    } else {
        std::cout << "Score 1 e diferente de Score 2.\n";
    }

    if (score1 != score2) {
        std::cout << "Score 1 e diferente de Score 2.\n";
    } else {
        std::cout << "Score 1 e igual a Score 2.\n";
    }

    if (!score1) {
        std::cout << "Score 1 e zero.\n";
    } else {
        std::cout << "Score 1 nao e zero.\n";
    }

    return 0;

}

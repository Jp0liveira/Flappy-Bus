#include <iostream>
#include "main_includes.h"

int main() {
     SpaceBus myCar(2, 5.7, "Meu veiculo", "SpaceBus Jump"); 
     std::cout << "Informacoes antes de carregar os dados:\n";
     std::cout << myCar;
    // Carregar variáveis do arquivo
    if (myCar.loadVariablesFromFile("config.txt")) {
        // Processar variáveis e exibir informações
        std::cout << "Informacoes apos carregar os dados:\n";
        std::cout << myCar;

        // Salvando as variáveis em um novo arquivo
        myCar.saveVariablesToFile("new_config.txt");
    }

    return 0;

}

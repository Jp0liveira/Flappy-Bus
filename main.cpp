#include <iostream>
#include "main_includes.h"

int main() {
   
    HotAirBalloon balloon1(0, 10.0);
    std::cout << "Informacoes iniciais do Balao:\n";
    std::cout << balloon1;
        
    std::cout << "Informacoes antes de carregar os dados:\n";
    std::cout << balloon1;
    // Carregar variáveis do arquivo
    if (balloon1.loadVariablesFromFile("config.txt")) {
        // Processar variáveis e exibir informações
        std::cout << "Informacoes apos carregar os dados:\n";
        std::cout <<balloon1;

        // Salvando as variáveis em um novo arquivo
        balloon1.saveVariablesToFile("new_config.txt");
    }   
    
    return 0;

}

#pragma once
#include <iostream>

class FireControl {
    
    public:
        FireControl();
        FireControl(const FireControl& other);
        virtual ~FireControl();

        // Funcionalidade específica de controle de fogo
        virtual void ignite() = 0;  // Método para iniciar o fogo
        virtual void extinguish() = 0;  // Método para apagar o fogo

        // Descrição do controle de fogo
        virtual std::string getDescription() const = 0;
};

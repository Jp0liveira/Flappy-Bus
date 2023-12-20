#pragma once
#include <iostream>

class WaterControl {
    
    public:
        WaterControl();
        WaterControl(const WaterControl& other);
        virtual ~WaterControl();

        // Funcionalidades específicas de controle de água
        virtual void fill() = 0;  // Método para encher o balão com água
        virtual void release() = 0;  // Método para liberar água do balão

        // Descrição do controle de água
        virtual std::string getDescription() const = 0;
};

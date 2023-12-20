#pragma once
#include "HotAirBalloon.h"
#include "FireControl.h"

class FireBalloon : public HotAirBalloon, public FireControl {
     friend std::ostream& operator<<(std::ostream& os, const FireBalloon& fireBalloon);
    public:
        FireBalloon();
        FireBalloon(int initialPosition, double initialVelocity);
        FireBalloon(const FireBalloon& other);
        virtual ~FireBalloon();

        // Implementações de FireControl
        void ignite() override;
        void extinguish() override;

        // Descrição específica para FireBalloon
        std::string getDescription() const override;

        void spreadFire();

        // Sobrecarga dos operadores
        FireBalloon& operator=(const FireBalloon& other);
        bool operator==(const FireBalloon& other) const;
        bool operator!=(const FireBalloon& other) const;
        bool operator!() const;

        // Métodos para leitura, processamento e salvamento de variáveis
        bool loadVariablesFromFile(const std::string& filename);
        bool processVariables(const std::map<std::string, double>& numericVariables, const std::map<std::string, std::string>& stringVariables, const std::map<std::string, bool>& boolVariables);
        bool saveVariablesToFile(const std::string& filename) const;

    private:
        bool isOnFire = false;  // Flag para rastrear se o balão está em chamas
};

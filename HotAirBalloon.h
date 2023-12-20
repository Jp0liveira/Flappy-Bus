#pragma once
#include "FloatingObstacle.h"

class HotAirBalloon : public FloatingObstacle {
        friend std::ostream& operator<<(std::ostream& os, const HotAirBalloon& hotAirBalloon);
    public:
        HotAirBalloon();
        HotAirBalloon(int initialPosition, double initialVelocity);
        HotAirBalloon(const HotAirBalloon& other);
        virtual ~HotAirBalloon();
        
        // Implementações concretas para métodos virtuais herdados
        void floatInAir() override;
        void applyWindForce() override;

        void releaseGas();

        // Sobrecarga dos operadores
        HotAirBalloon& operator=(const HotAirBalloon& other);
        bool operator==(const HotAirBalloon& other) const;
        bool operator!=(const HotAirBalloon& other) const;
        bool operator!() const;

        // Métodos para leitura, processamento e salvamento de variáveis
        bool loadVariablesFromFile(const std::string& filename);
        bool processVariables(const std::map<std::string, double>& numericVariables, const std::map<std::string, std::string>& stringVariables, const std::map<std::string, bool>& boolVariables);
        bool saveVariablesToFile(const std::string& filename) const;
        
    private:
        double gasLevel;  // Atributo para simular o nível de gás no balão    

};

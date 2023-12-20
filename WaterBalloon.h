#pragma once
#include "HotAirBalloon.h"
#include "WaterControl.h"

class WaterBalloon : public HotAirBalloon, public WaterControl {
        friend std::ostream& operator<<(std::ostream& os, const WaterBalloon& waterBalloon);
    public:
        WaterBalloon();
        WaterBalloon(int initialPosition, double initialVelocity);
        WaterBalloon(const WaterBalloon& other);
        virtual ~WaterBalloon();

        // Implementações de WaterControl
        void fill() override;
        void release() override;

        // Descrição específica para WaterBalloon
        std::string getDescription() const override;

        void createWaterPatterns(int patternType, int intensity);

        // Sobrecarga dos operadores
        WaterBalloon& operator=(const WaterBalloon& other);
        bool operator==(const WaterBalloon& other) const;
        bool operator!=(const WaterBalloon& other) const;
        bool operator!() const;

        // Métodos para leitura, processamento e salvamento de variáveis
        bool loadVariablesFromFile(const std::string& filename);
        bool processVariables(const std::map<std::string, double>& numericVariables, const std::map<std::string, std::string>& stringVariables, const std::map<std::string, bool>& boolVariables);
        bool saveVariablesToFile(const std::string& filename) const;
};

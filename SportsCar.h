#pragma once
#include "Vehicle.h"

class SportsCar : public Vehicle {

      friend std::ostream& operator<<(std::ostream& os, const SportsCar& sportsCar);

    public:
        SportsCar();
        SportsCar(int initialPosition, double initialVelocity, const std::string& name, int fuelCapacity, const std::string& fuelType, bool turbo);
        SportsCar(const SportsCar& other);
        virtual ~SportsCar();

        bool hasTurbo() const;
        void toggleTurbo();
        void accelerateWithTurbo();
        virtual void displayInfo() const override;

        SportsCar& operator=(const SportsCar& other);
        bool operator==(const SportsCar& other) const;
        bool operator!=(const SportsCar& other) const;
        bool operator!() const;

        // Métodos para leitura, processamento e salvamento de variáveis
        bool loadVariablesFromFile(const std::string& filename);
        bool processVariables(const std::map<std::string, double>& variables, const std::map<std::string, std::string>& stringVariables, std::map<std::string, bool> boolVariables);
        bool saveVariablesToFile(const std::string& filename) const;

    private:
        bool turbo;
};

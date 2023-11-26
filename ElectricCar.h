#pragma once

#include "Vehicle.h"

class ElectricCar : public Vehicle {
        friend std::ostream& operator<<(std::ostream& os, const ElectricCar& electricCar);
    public:
        ElectricCar();
        ElectricCar(int initialPosition, double initialVelocity, const std::string& name, int fuelCapacity, int batteryCapacity, const std::string& connectorType);
        ElectricCar(const ElectricCar& other);
        virtual ~ElectricCar();

        static const std::string fuelTypeElectric;

        void chargeBattery(int chargeAmount);
        void disconnectCharger();
        void displayInfo() const override;

        ElectricCar& operator=(const ElectricCar& other);
        bool operator==(const ElectricCar& other) const;
        bool operator!=(const ElectricCar& other) const;
        bool operator!() const;

        bool loadVariablesFromFile(const std::string& filename);
        bool processVariables(const std::map<std::string, double>& numericVariables, const std::map<std::string, std::string>& stringVariables);
        bool saveVariablesToFile(const std::string& filename) const;
        
        void setBatteryCapacity(int batteryCapacity);
        void setConnectorType(const std::string& connectorType);
        int getBatteryCapacity() const;
        std::string getConnectorType() const;

    private:
        int batteryCapacity;
        std::string connectorType;
        bool isCharging = false;

};

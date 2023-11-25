#pragma once
#include <iostream>
#include "FlappyBus.h"
#include <fstream>
#include <sstream>
#include <cctype>
#include <iomanip>
#include <algorithm>



class Vehicle : public FlappyBus {
         friend std::ostream& operator<<(std::ostream& os, const Vehicle& vehicle);
    public:
        Vehicle();
        Vehicle(int initialPosition, double initialVelocity, const std::string& name, int fuelCapacity, const std::string& fuelType);
        Vehicle(const Vehicle&);
        virtual ~Vehicle();

        virtual void refuel(int amount);
        virtual void honk() const;
        virtual void displayInfo() const;

        void setFuelCapacity(int fuelCapacity);
        void setfuelType(const std::string& fuelType);
        int getFuelCapacity();
        std::string getFuelType() const;

        Vehicle& operator=(const Vehicle& other);
        bool operator==(const Vehicle& other) const;
        bool operator!=(const Vehicle& other) const;
        bool operator!() const;

        // Métodos para leitura, processamento e salvamento de variáveis
        bool loadVariablesFromFile(const std::string& filename);
        bool processVariables(const std::map<std::string, double>& variables, const std::map<std::string, std::string>& stringVariables);
        bool saveVariablesToFile(const std::string& filename) const;

    protected:
        int fuelCapacity;
        std::string fuelType;
};
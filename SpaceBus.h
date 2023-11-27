#pragma once
#include "FlappyBus.h"

class SpaceBus : public FlappyBus {
        friend std::ostream& operator<<(std::ostream& os, const SpaceBus& spaceBus);
    public:
        SpaceBus();
        SpaceBus(int initialPosition, double initialVelocity, const std::string& name, const std::string& propulsionType);
        SpaceBus(const SpaceBus& other);
        virtual ~SpaceBus();

        virtual void openHatch();
        virtual void closeHatch();
        virtual void adjustEnvironmentalControl(double temperature, double pressure, double oxygenLevel);
        virtual void setDestination(const std::string& destination);
        virtual void navigate();

        SpaceBus& operator=(const SpaceBus& other);
        bool operator==(const SpaceBus& other) const;
        bool operator!=(const SpaceBus& other) const;
        bool operator!() const;

        bool loadVariablesFromFile(const std::string& filename);
        bool processVariables(const std::map<std::string, double>& numericVariables, const std::map<std::string, std::string>& stringVariables);
        bool saveVariablesToFile(const std::string& filename) const;
        bool isNumeric(const std::string& str);

        std::string getPropulsionType() const;
        void setPropulsionType(const std::string& propulsionType);
        bool isHatchOpen() const;
        void setHatchOpen(bool hatchOpen);
        double getEnvironmentalTemperature() const;
        void setEnvironmentalTemperature(double temperature);
        double getEnvironmentalPressure() const;
        void setEnvironmentalPressure(double pressure);
        double getEnvironmentalOxygenLevel() const;
        void setEnvironmentalOxygenLevel(double oxygenLevel);
        std::string getDestination() const;
     
    protected:
        std::string propulsionType;
        bool hatchOpen;
        double environmentalTemperature;
        double environmentalPressure;
        double environmentalOxygenLevel;
        std::string destination;
};

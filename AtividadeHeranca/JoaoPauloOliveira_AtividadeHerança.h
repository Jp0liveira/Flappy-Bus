/*Criar três hierarquia, sendo duas de três níveis, como explicado em sala e 
no Classroom. Fazer a sobrecarga para cada classe dos operadores =, ==, ≠, ! e << 
(friend). Usar sempre que possível o static_cast para reaproveitamento de código. 
Para cada classe do seu projeto criar pelo menos três constructores, 
sendo um o constructor de cópia. É necessário ter a funcionalidade: 1. 
leitura de arquivos para configuração das suas classes e variáveis de status, 2. 
processamento das variáveis de status e 3. salvamento dessas variáveis. 
Sem o diagrama UML, a saída do programa e o vídeo, o trabalho não será avaliado.*/


//// Geral - parte para revisão
    //Diagrama UML    
    //Organização do código 

//// O .h das classes bases

     ////Classe base 1    
#pragma once
#include <string>
#include <map>
#include <vector>
#include "ScoreManager.h"
#include "PowerUp.h"
#include <chrono>
#include <thread> 
#include <fstream>
#include <sstream>
#include <cctype>
#include <iomanip>
#include <algorithm>


struct ObstaculoEmMovimento {
    int positionX;
    int positionY;
    double speedX;
    double speedY;

    ObstaculoEmMovimento(int posX, int posY, double spdX, double spdY);
};

struct ObstaculoEstatico {
    int positionX;
    int positionY;
    int width;
    int height;

    ObstaculoEstatico(int posX, int posY, int w, int h);
};

class FlappyBus {
         friend std::ostream& operator<<(std::ostream& os, const FlappyBus& flappyBus);
    public:
        // Construtor padrão
        FlappyBus();
        // Construtor com parâmetros
        FlappyBus(int initialPosition, double initialVelocity, const std::string& name);
        FlappyBus(const FlappyBus&);
        ~FlappyBus();

        // Getters e setters
        int getPosition() const;
        double getVelocity() const;
        int getScore() const;
        bool getHadCollision();
        int MaxScore(const ScoreManager& );
        std::string getPlayerName() const;

        void setPosition(int);
        void setVelocity(double);
        void setPlayerName(const std::string&);
        void setHadCollision(bool);

        // Métodos adicionais
        void jump(); // Usa a classe ScoreManager
        void displayInfo() const;
        bool didCollide();

         // Sobrecarga de operadores
        FlappyBus& operator=(const FlappyBus& other);
        bool operator==(const FlappyBus& other) const;
        bool operator!=(const FlappyBus& other) const;
        bool operator!() const;
        
        // Métodos para registro de eventos do jogo
        void addEvent(const std::string& eventDescription);
        void displayEventLog() const;
        
        // Uso do STL MAP
        std::map<int, std::string> getPlayerEvents() const;
        
        // Uso das Structs
        void addObstaculoEmMovimento(int posX, int posY, double spdX, double spdY);
        void addObstaculoEstatico(int posX, int posY, int w, int h);

        // Métodos para PowerUps
        void addPowerUp(const PowerUp& powerUp);
        void usePowerUp(const PowerUp& powerUp);
        bool hasPowerUp(const std::string& powerUpName) const;

        bool isUsingPowerUp() { return usingPowerUp;};

        // Métodos para carregamento de arquivos
        bool loadVariablesFromFile(const std::string& filename);
        bool processVariables(const std::map<std::string, double>& numericVariables, const std::map<std::string, std::string>& stringVariables);
        bool saveVariablesToFile(const std::string& filename) const;
        bool isNumeric(const std::string& str);

    private:
        int position;
        double velocity;
        int score;
        std::string playerName;
        bool hadCollision = false;
        
        // Uso da classe ScoreManager
        ScoreManager scoreManager;
        
        void update();
        void increaseScore();

        // Registro de eventos do jogo
        std::string* eventLog;
        int eventLogSize;
        int eventCount;

        void allocateMemory(int newSize);

        // Uso das Structs
        std::vector<ObstaculoEmMovimento> obstaculosEmMovimento;
        std::vector<ObstaculoEstatico> obstaculosEstaticos;

        // Uso da classe powerUp
        std::vector<PowerUp> powerUps;
        double baseVelocity; // Velocidade normal do FlappyBus
        std::chrono::steady_clock::time_point powerUpStartTime;
        std::chrono::seconds powerUpDuration;
        bool usingPowerUp =  false;
       
};

     ////Classe base 2
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
        int getFuelCapacity() const;
        std::string getFuelType() const;

        Vehicle& operator=(const Vehicle& other);
        bool operator==(const Vehicle& other) const;
        bool operator!=(const Vehicle& other) const;
        bool operator!() const;

        // Métodos para leitura, processamento e salvamento de variáveis
        bool loadVariablesFromFile(const std::string& filename);
        bool processVariables(const std::map<std::string, double>& variables, const std::map<std::string, std::string>& stringVariables);
        bool saveVariablesToFile(const std::string& filename) const;
        bool isNumeric(const std::string& str);

    protected:
        int fuelCapacity;
        std::string fuelType;
};
     ////Classe base 3
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

//// O .h da hierarquia 1

     ////Classe 1
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
        int getFuelCapacity() const;
        std::string getFuelType() const;

        Vehicle& operator=(const Vehicle& other);
        bool operator==(const Vehicle& other) const;
        bool operator!=(const Vehicle& other) const;
        bool operator!() const;

        // Métodos para leitura, processamento e salvamento de variáveis
        bool loadVariablesFromFile(const std::string& filename);
        bool processVariables(const std::map<std::string, double>& variables, const std::map<std::string, std::string>& stringVariables);
        bool saveVariablesToFile(const std::string& filename) const;
        bool isNumeric(const std::string& str);

    protected:
        int fuelCapacity;
        std::string fuelType;
};
     ////Classe 2
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

     ///E assim por diante

//// O .h da hierarquia 2

     ////Classe 1
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

     ////Classe 2
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


//// Mostrar implementação de método que especializa a derivada
 /// Mostrar reaproveitamente de código da base

    //// Hierarquia 1

         ////Classe 1
#include "Vehicle.h"

Vehicle::Vehicle(): FlappyBus(){
    this->setFuelCapacity(100);
    this->setfuelType("Gasolina");
}

Vehicle::Vehicle(int initialPosition, double initialVelocity, const std::string& name, int fuelCapacity, const std::string& fuelType): FlappyBus(initialPosition, initialVelocity, name), fuelType(fuelType) {
    this->setFuelCapacity(fuelCapacity);
    this->setfuelType(fuelType);
}

Vehicle::Vehicle(const Vehicle& other) : FlappyBus(other) {
    this->fuelCapacity = other.fuelCapacity;
    this->fuelType = other.fuelType;
}

Vehicle::~Vehicle() {}

void Vehicle::refuel(int amount) {
    fuelCapacity += amount;
    std::cout << FlappyBus::getPlayerName() << " foi abastecido. Nova capacidade de combustivel: " << fuelCapacity << " litros.\n";
}

void Vehicle::honk() const {
    std::cout << FlappyBus::getPlayerName() << " buzina: Honk! Honk!\n";
}

void Vehicle::displayInfo() const {
    FlappyBus::displayInfo();
    std::cout << "Capacidade de combustivel: " << this->fuelCapacity << " litros\n";
    std::cout << "Tipo de combustivel: " << this->fuelType << "\n";
}

// Sobrecarga dos Operadores
Vehicle& Vehicle::operator=(const Vehicle& other) {
    if (this == &other) {
        return *this;
    }

    // Chama o operador de atribuição da classe base (FlappyBus)
    static_cast<FlappyBus&>(*this) = other;

    this->fuelCapacity = other.fuelCapacity;
    this->fuelType = other.fuelType;

    return *this;
}

bool Vehicle::operator==(const Vehicle& other) const {
    if (this == &other) {
        return true;
    }

    // Compara a parte da classe base (FlappyBus)
    if (static_cast<const FlappyBus&>(*this) != static_cast<const FlappyBus&>(other)) {
        return false;
    }

    return this->fuelCapacity == other.fuelCapacity &&
           this->fuelType == other.fuelType;
}

bool Vehicle::operator!=(const Vehicle& other) const {
    return !(*this == other);
}

bool Vehicle::operator!() const {
    // Usa a negação da classe base (FlappyBus)
    return !static_cast<const FlappyBus&>(*this);
}

std::ostream& operator<<(std::ostream& os, const Vehicle& vehicle) {
    // Usa a sobrecarga da classe base (FlappyBus)
    os << static_cast<const FlappyBus&>(vehicle);

    os << "Capacidade de combustivel: " << vehicle.fuelCapacity << " litros\n";
    os << "Tipo de combustivel: " << vehicle.fuelType << "\n";

    return os;
}

// Carregamento de arquivos
bool Vehicle::isNumeric(const std::string& str) {
    return !str.empty() && std::all_of(str.begin(), str.end(), [](char c) {
        return std::isdigit(c) || c == '.' || c == '-';
    });
}

bool Vehicle::loadVariablesFromFile(const std::string& filename) {
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file: " << filename << '\n';
        return false;
    }

    std::map<std::string, double> numericVariables;
    std::map<std::string, std::string> stringVariables;

    std::string line;
    std::string variableName;
    char equalsSign;
    std::string value;

    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        if (iss >> variableName >> equalsSign >> value && equalsSign == '=') {
            // Verifica se a string pode ser convertida para um número
            if (isNumeric(value)) {
                double numericValue = std::stod(value);
                numericVariables[variableName] = numericValue;
            } else {
                stringVariables[variableName] = value;
            }
        } else {
            std::cerr << "Error parsing line: " << line << '\n';
        }
    }
    inputFile.close();
    return processVariables(numericVariables, stringVariables);

}


bool Vehicle::processVariables(const std::map<std::string, double>& numericVariables, const std::map<std::string, std::string>& stringVariables) {
    if (numericVariables.find("initialPosition") != numericVariables.end())
        setPosition(numericVariables.at("initialPosition"));

    if (numericVariables.find("initialVelocity") != numericVariables.end())
        setVelocity(numericVariables.at("initialVelocity"));

    if (stringVariables.find("name") != stringVariables.end())
        setPlayerName(stringVariables.at("name"));

    if (numericVariables.find("fuelCapacity") != numericVariables.end())
        this->fuelCapacity = static_cast<int>(numericVariables.at("fuelCapacity"));

    if (stringVariables.find("fuelType") != stringVariables.end())
        this->fuelType = stringVariables.at("fuelType");

    return true;
}

bool Vehicle::saveVariablesToFile(const std::string& filename) const {
    std::ofstream outputFile(filename);
    if (!outputFile.is_open()) {
        std::cerr << "Error opening file for writing: " << filename << '\n';
        return false;
    }

    outputFile << "initialPosition = " << getPosition() << '\n';
    outputFile << "initialVelocity = " << getVelocity() << '\n';
    outputFile << "name = " << getPlayerName() << '\n';
    outputFile << "fuelCapacity = " << this->fuelCapacity << '\n';
    outputFile << "fuelType = " << this->fuelType << '\n';

    outputFile.close();

    return true;
}

         ////Classe 2
#include "SpaceBus.h"

SpaceBus::SpaceBus() : FlappyBus(), propulsionType("Unknown"), hatchOpen(false), environmentalTemperature(22.0), environmentalPressure(1.0), environmentalOxygenLevel(20.9), destination("Undefined") {}

SpaceBus::SpaceBus(int initialPosition, double initialVelocity, const std::string& name, const std::string& propulsionType): FlappyBus(initialPosition, initialVelocity, name), propulsionType(propulsionType), hatchOpen(false), environmentalTemperature(22.0), environmentalPressure(1.0), environmentalOxygenLevel(20.9), destination("Undefined") {}

SpaceBus::SpaceBus(const SpaceBus& other) : FlappyBus(other), propulsionType(other.propulsionType), hatchOpen(other.hatchOpen), environmentalTemperature(other.environmentalTemperature), environmentalPressure(other.environmentalPressure), environmentalOxygenLevel(other.environmentalOxygenLevel), destination(other.destination) {}

SpaceBus::~SpaceBus() {}

void SpaceBus::openHatch() {
    hatchOpen = true;
    std::cout << getPlayerName() << " abriu a escotilha espacial.\n";
}

void SpaceBus::closeHatch() {
    hatchOpen = false;
    std::cout << getPlayerName() << " fechou a escotilha espacial.\n";
}

void SpaceBus::adjustEnvironmentalControl(double temperature, double pressure, double oxygenLevel) {
    environmentalTemperature = temperature;
    environmentalPressure = pressure;
    environmentalOxygenLevel = oxygenLevel;
    std::cout << getPlayerName() << " ajustou o controle ambiental.\n";
}

void SpaceBus::setDestination(const std::string& newDestination) {
    destination = newDestination;
    std::cout << getPlayerName() << " definir o destino para " << destination << ".\n";
}

void SpaceBus::navigate() {
    std::cout << getPlayerName() << " esta navegando pelo espaco para chegar a " << destination << ".\n";
}


// Sobrecargas de Operadores
SpaceBus& SpaceBus::operator=(const SpaceBus& other) {
    if (this == &other) {
        return *this;
    }

    // Chama o operador de atribuição da classe base (FlappyBus)
    static_cast<FlappyBus&>(*this) = other;

    this->propulsionType = other.propulsionType;

    return *this;
}

bool SpaceBus::operator==(const SpaceBus& other) const {
    if (this == &other) {
        return true;
    }

    // Compara a parte da classe base (FlappyBus)
    if (static_cast<const FlappyBus&>(*this) != static_cast<const FlappyBus&>(other)) {
        return false;
    }

    return this->propulsionType == other.propulsionType;
}

bool SpaceBus::operator!=(const SpaceBus& other) const {
    return !(*this == other);
}

bool SpaceBus::operator!() const {
    // Usa a negação da classe base (FlappyBus)
    return !static_cast<const FlappyBus&>(*this);
}

std::ostream& operator<<(std::ostream& os, const SpaceBus& spaceBus) {
    // Usa a sobrecarga da classe base (FlappyBus)
    os << static_cast<const FlappyBus&>(spaceBus);

    os << "Tipo de Propulsao: " << spaceBus.propulsionType << "\n";

    return os;
}

// Carregamento de arquivos
bool SpaceBus::isNumeric(const std::string& str) {
    return !str.empty() && std::all_of(str.begin(), str.end(), [](char c) {
        return std::isdigit(c) || c == '.' || c == '-';
    });
}

bool SpaceBus::loadVariablesFromFile(const std::string& filename) {
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file: " << filename << '\n';
        return false;
    }

    std::map<std::string, double> numericVariables;
    std::map<std::string, std::string> stringVariables;

    std::string line;
    std::string variableName;
    char equalsSign;
    std::string value;

    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        if (iss >> variableName >> equalsSign >> value && equalsSign == '=') {
            if (isNumeric(value)) {
                double numericValue = std::stod(value);
                numericVariables[variableName] = numericValue;
            } else {
                stringVariables[variableName] = value;
            }
        } else {
            std::cerr << "Error parsing line: " << line << '\n';
        }
    }

    inputFile.close();
    return processVariables(numericVariables, stringVariables);
}

bool SpaceBus::processVariables(const std::map<std::string, double>& numericVariables, const std::map<std::string, std::string>& stringVariables) {
   if (numericVariables.find("initialPosition") != numericVariables.end())
        setPosition(numericVariables.at("initialPosition"));

    if (numericVariables.find("initialVelocity") != numericVariables.end())
        setVelocity(numericVariables.at("initialVelocity"));

    if (stringVariables.find("name") != stringVariables.end())
        setPlayerName(stringVariables.at("name"));

    if (stringVariables.find("propulsionType") != stringVariables.end())
        this->propulsionType = stringVariables.at("propulsionType");

    return true;
}

bool SpaceBus::saveVariablesToFile(const std::string& filename) const {
    std::ofstream outputFile(filename);
    if (!outputFile.is_open()) {
        std::cerr << "Error opening file for writing: " << filename << '\n';
        return false;
    }

    outputFile << "initialPosition = " << getPosition() << '\n';
    outputFile << "initialVelocity = " << getVelocity() << '\n';
    outputFile << "name = " << getPlayerName() << '\n';
    outputFile << "propulsionType = " << this->propulsionType << '\n';

    outputFile.close();

    return true;
}

    //// Hierarquia 2

         ////Classe 1
#include "ElectricCar.h"


const std::string ElectricCar::fuelTypeElectric = "Eletrico";

ElectricCar::ElectricCar() : Vehicle(), batteryCapacity(0), connectorType("Type 2") {}

ElectricCar::ElectricCar(int initialPosition, double initialVelocity, const std::string& name, int fuelCapacity, int batteryCapacity, const std::string& connectorType)
    : Vehicle(initialPosition, initialVelocity, name, fuelCapacity, fuelTypeElectric), batteryCapacity(batteryCapacity), connectorType(connectorType) {}

ElectricCar::ElectricCar(const ElectricCar& other) : Vehicle(other), batteryCapacity(other.batteryCapacity), connectorType(other.connectorType) {}

ElectricCar::~ElectricCar() {}

void ElectricCar::chargeBattery(int chargeAmount) {
    if (isCharging) {
        std::cout << "O carro eletrico " << getPlayerName() << " ja esta carregando.\n";
    } else {
        isCharging = true;
        batteryCapacity += chargeAmount;
        std::cout << "Carregando o carro eletrico " << getPlayerName() << ". Capacidade de carga: " << this->batteryCapacity << " kWh\n";
    }
}

void ElectricCar::disconnectCharger() {
    if (!isCharging) {
        std::cout << "O carro eletrico "<< getPlayerName() << "nao esta carregando no momento.\n";
    } else {
        isCharging = false;
        std::cout << "Carregador desconectado. Capacidade de carga: " << batteryCapacity << " kWh\n";
    }
}

void ElectricCar::displayInfo() const {
    Vehicle::displayInfo();
    std::cout << "Capacidade de carga: " << batteryCapacity << " kWh\n";
    std::cout << "Tipo de conector: " << connectorType << "\n";
    std::cout << "Status de carregamento: " << (isCharging ? "Carregando" : "Nao esta carregando") << "\n";
}

// Sobrecarga dos Operadores
ElectricCar& ElectricCar::operator=(const ElectricCar& other) {
    if (this == &other) {
        return *this;
    }

    // Chama o operador de atribuição da classe base (Vehicle)
    static_cast<Vehicle&>(*this) = other;

    this->batteryCapacity = other.batteryCapacity;
    this->connectorType = other.connectorType;

    return *this;
}

bool ElectricCar::operator==(const ElectricCar& other) const {
    if (this == &other) {
        return true;
    }

    // Compara a parte da classe base (Vehicle)
    if (static_cast<const Vehicle&>(*this) != static_cast<const Vehicle&>(other)) {
        return false;
    }

    return this->batteryCapacity == other.batteryCapacity &&
           this->connectorType == other.connectorType;
}

bool ElectricCar::operator!=(const ElectricCar& other) const {
    return !(*this == other);
}

bool ElectricCar::operator!() const {
    // Usa a negação da classe base (Vehicle)
    return !static_cast<const Vehicle&>(*this);
}

std::ostream& operator<<(std::ostream& os, const ElectricCar& electricCar) {
    // Usa a sobrecarga da classe base (Vehicle)
    os << static_cast<const Vehicle&>(electricCar);

    os << "Capacidade da bateria: " << electricCar.batteryCapacity << " kWh\n";
    os << "Tipo de conector: " << electricCar.connectorType << "\n";

    return os;
}

// Carregamento de arquivos
bool ElectricCar::loadVariablesFromFile(const std::string& filename) {
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file: " << filename << '\n';
        return false;
    }

    std::map<std::string, double> numericVariables;
    std::map<std::string, std::string> stringVariables;

    std::string line;
    std::string variableName;
    char equalsSign;
    std::string value;

    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        if (iss >> variableName >> equalsSign >> value && equalsSign == '=') {
            if (Vehicle::isNumeric(value)) {
                double numericValue = std::stod(value);
                numericVariables[variableName] = numericValue;
            } else {
                stringVariables[variableName] = value;
            }
        } else {
            std::cerr << "Error parsing line: " << line << '\n';
        }
    }

    inputFile.close();
    return processVariables(numericVariables, stringVariables);
}

bool ElectricCar::processVariables(const std::map<std::string, double>& numericVariables, const std::map<std::string, std::string>& stringVariables) {
    if (!Vehicle::processVariables(numericVariables, stringVariables)) {
        return false;
    }

    if (numericVariables.find("batteryCapacity") != numericVariables.end())
        this->batteryCapacity = static_cast<int>(numericVariables.at("batteryCapacity"));

    if (stringVariables.find("connectorType") != stringVariables.end())
        this->connectorType = stringVariables.at("connectorType");

    return true;
}

bool ElectricCar::saveVariablesToFile(const std::string& filename) const {
    std::ofstream outputFile(filename);
    if (!outputFile.is_open()) {
        std::cerr << "Error opening file for writing: " << filename << '\n';
        return false;
    }

    outputFile << "initialPosition = " << getPosition() << '\n';
    outputFile << "initialVelocity = " << getVelocity() << '\n';
    outputFile << "name = " << getPlayerName() << '\n';
    outputFile << "fuelCapacity = " << getFuelCapacity() << '\n';
    outputFile << "fuelType = " << this->fuelTypeElectric << '\n';
    outputFile << "batteryCapacity = " << this->batteryCapacity << '\n';
    outputFile << "connectorType = " << this->connectorType << '\n';

    outputFile.close();

    return true;
}

         ////Classe 2
#include "SportsCar.h"

SportsCar::SportsCar() : Vehicle(), turbo(false) {}

SportsCar::SportsCar(int initialPosition, double initialVelocity, const std::string& name, int fuelCapacity, const std::string& fuelType, bool turbo)
    : Vehicle(initialPosition, initialVelocity, name, fuelCapacity, fuelType), turbo(turbo) {
}

SportsCar::SportsCar(const SportsCar& other) : Vehicle(other), turbo(other.turbo) {}

SportsCar::~SportsCar() {}

void SportsCar::toggleTurbo() {
    turbo = !turbo;
    std::cout << "Turbo " << (turbo ? "ativado" : "desativado") << " para o carro esportivo."  << getPlayerName() << "\n";
}

void SportsCar::accelerateWithTurbo() {
    if (turbo) {
        setVelocity(getVelocity() + 20);
    }
}

void SportsCar::displayInfo() const {
    Vehicle::displayInfo(); 
    std::cout << "Carro esportivo\n";
    std::cout << "Turbo: " << (turbo ? "ativado" : "desativado") << "\n";
}

// Sobrecarga dos Operadores
SportsCar& SportsCar::operator=(const SportsCar& other) {
    if (this == &other) {
        return *this;
    }
    // Chama o operador de atribuição da classe base (Vehicle)
    static_cast<Vehicle&>(*this) = other;

    // Adiciona atributos específicos de SportsCar
    this->turbo = other.turbo;

    return *this;
}

bool SportsCar::operator==(const SportsCar& other) const {
    if (this == &other) {
        return true;
    }

    // Compara a parte da classe base (Vehicle)
    if (static_cast<const Vehicle&>(*this) != static_cast<const Vehicle&>(other)) {
        return false;
    }

    return this->turbo == other.turbo;
}

bool SportsCar::operator!=(const SportsCar& other) const {
    return !(*this == other);
}

bool SportsCar::operator!() const {
    // Usa a negação da classe base (Vehicle)
    return !static_cast<const Vehicle&>(*this);
}

std::ostream& operator<<(std::ostream& os, const SportsCar& sportsCar) {
    // Usa a sobrecarga da classe base (Vehicle)
    os << static_cast<const Vehicle&>(sportsCar);

    os << "Carro esportivo\n";
    os << "Turbo: " << (sportsCar.turbo ? "ativado" : "desativado") << "\n";

    return os;
}

// Carregamento de arquivos
bool SportsCar::loadVariablesFromFile(const std::string& filename) {
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file: " << filename << '\n';
        return false;
    }

    std::map<std::string, double> numericVariables;
    std::map<std::string, std::string> stringVariables;
    std::map<std::string, bool> boolVariables;

    std::string line;
    std::string variableName;
    char equalsSign;
    std::string value;

    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        if (iss >> variableName >> equalsSign >> value && equalsSign == '=') {
            if (Vehicle::isNumeric(value)) {
                double numericValue = std::stod(value);
                numericVariables[variableName] = numericValue;
            }else if (value == "true" || value == "false") {
                bool boolValue = (value == "true");
                boolVariables[variableName] = boolValue;
            } else {
                stringVariables[variableName] = value;
            }
        } else {
            std::cerr << "Error parsing line: " << line << '\n';
        }
    }
    inputFile.close();
    return processVariables(numericVariables, stringVariables, boolVariables);

}


bool SportsCar::processVariables(const std::map<std::string, double>& numericVariables, const std::map<std::string, std::string>& stringVariables, std::map<std::string, bool> boolVariables) {
    if (numericVariables.find("initialPosition") != numericVariables.end())
        setPosition(numericVariables.at("initialPosition"));

    if (numericVariables.find("initialVelocity") != numericVariables.end())
        setVelocity(numericVariables.at("initialVelocity"));

    if (stringVariables.find("name") != stringVariables.end())
        setPlayerName(stringVariables.at("name"));

    if (numericVariables.find("fuelCapacity") != numericVariables.end())
        setFuelCapacity(static_cast<int>(numericVariables.at("fuelCapacity")));

    if (stringVariables.find("fuelType") != stringVariables.end())
        setfuelType(stringVariables.at("fuelType"));

    if (boolVariables.find("turbo") != boolVariables.end())
        this->turbo = boolVariables.at("turbo");

    return true;
}

bool SportsCar::saveVariablesToFile(const std::string& filename) const {
    std::ofstream outputFile(filename);
    if (!outputFile.is_open()) {
        std::cerr << "Error opening file for writing: " << filename << '\n';
        return false;
    }

    outputFile << "initialPosition = " << getPosition() << '\n';
    outputFile << "initialVelocity = " << getVelocity() << '\n';
    outputFile << "name = " << getPlayerName() << '\n';
    outputFile << "fuelCapacity = " << getFuelCapacity() << '\n';
    outputFile << "fuelType = " << getFuelType() << '\n';
    outputFile << "turbo = " << this->turbo << '\n';

    outputFile.close();

    return true;
}


//// Fazer a sobrecarga para todas as classes dos operadores =, ==, ≠ e << (friend)

     //// Operator=
         //// Base 1
FlappyBus& FlappyBus::operator=(const FlappyBus& other) {
    if (this == &other) {
        return *this;
    }

    this->position = other.position;
    this->velocity = other.velocity;
    this->score = other.score;
    this->playerName = other.playerName;
    this->hadCollision = other.hadCollision;

    return *this;
}           
             ////Derivadas da Base 1 - mostrar uso static_cast
Vehicle& Vehicle::operator=(const Vehicle& other) {
    if (this == &other) {
        return *this;
    }

    // Chama o operador de atribuição da classe base (FlappyBus)
    static_cast<FlappyBus&>(*this) = other;

    this->fuelCapacity = other.fuelCapacity;
    this->fuelType = other.fuelType;

    return *this;
}

SpaceBus& SpaceBus::operator=(const SpaceBus& other) {
    if (this == &other) {
        return *this;
    }

    // Chama o operador de atribuição da classe base (FlappyBus)
    static_cast<FlappyBus&>(*this) = other;

    this->propulsionType = other.propulsionType;

    return *this;
}
         //// Base 2
Vehicle& Vehicle::operator=(const Vehicle& other) {
    if (this == &other) {
        return *this;
    }

    // Chama o operador de atribuição da classe base (FlappyBus)
    static_cast<FlappyBus&>(*this) = other;

    this->fuelCapacity = other.fuelCapacity;
    this->fuelType = other.fuelType;

    return *this;
}
             ////Derivadas da Base 2 - mostrar uso static_cast
SportsCar& SportsCar::operator=(const SportsCar& other) {
    if (this == &other) {
        return *this;
    }
    // Chama o operador de atribuição da classe base (Vehicle)
    static_cast<Vehicle&>(*this) = other;

    // Adiciona atributos específicos de SportsCar
    this->turbo = other.turbo;

    return *this;
}

ElectricCar& ElectricCar::operator=(const ElectricCar& other) {
    if (this == &other) {
        return *this;
    }

    // Chama o operador de atribuição da classe base (Vehicle)
    static_cast<Vehicle&>(*this) = other;

    this->batteryCapacity = other.batteryCapacity;
    this->connectorType = other.connectorType;

    return *this;
}
     //// Operators== e !=
         //// Base 1
bool FlappyBus::operator==(const FlappyBus& other) const {
    if (this == &other) {
        return true;
    }

    return this->position == other.position &&
           this->velocity == other.velocity &&
           this->score == other.score &&
           this->playerName == other.playerName &&
           this->hadCollision == other.hadCollision;
}

bool FlappyBus::operator!=(const FlappyBus& other) const {
    return !(*this == other);
}
             ////Derivadas da Base 1 - mostrar uso static_cast
bool Vehicle::operator==(const Vehicle& other) const {
    if (this == &other) {
        return true;
    }

    // Compara a parte da classe base (FlappyBus)
    if (static_cast<const FlappyBus&>(*this) != static_cast<const FlappyBus&>(other)) {
        return false;
    }

    return this->fuelCapacity == other.fuelCapacity &&
           this->fuelType == other.fuelType;
}

bool Vehicle::operator!=(const Vehicle& other) const {
    return !(*this == other);
}

bool SpaceBus::operator==(const SpaceBus& other) const {
    if (this == &other) {
        return true;
    }

    // Compara a parte da classe base (FlappyBus)
    if (static_cast<const FlappyBus&>(*this) != static_cast<const FlappyBus&>(other)) {
        return false;
    }

    return this->propulsionType == other.propulsionType;
}

bool SpaceBus::operator!=(const SpaceBus& other) const {
    return !(*this == other);
}
         //// Base 2
bool Vehicle::operator==(const Vehicle& other) const {
    if (this == &other) {
        return true;
    }

    // Compara a parte da classe base (FlappyBus)
    if (static_cast<const FlappyBus&>(*this) != static_cast<const FlappyBus&>(other)) {
        return false;
    }

    return this->fuelCapacity == other.fuelCapacity &&
           this->fuelType == other.fuelType;
}

bool Vehicle::operator!=(const Vehicle& other) const {
    return !(*this == other);
}
             ////Derivadas da Base 2 - mostrar uso static_cast

bool SportsCar::operator==(const SportsCar& other) const {
    if (this == &other) {
        return true;
    }

    // Compara a parte da classe base (Vehicle)
    if (static_cast<const Vehicle&>(*this) != static_cast<const Vehicle&>(other)) {
        return false;
    }

    return this->turbo == other.turbo;
}

bool SportsCar::operator!=(const SportsCar& other) const {
    return !(*this == other);
}


bool ElectricCar::operator==(const ElectricCar& other) const {
    if (this == &other) {
        return true;
    }

    // Compara a parte da classe base (Vehicle)
    if (static_cast<const Vehicle&>(*this) != static_cast<const Vehicle&>(other)) {
        return false;
    }

    return this->batteryCapacity == other.batteryCapacity &&
           this->connectorType == other.connectorType;
}

bool ElectricCar::operator!=(const ElectricCar& other) const {
    return !(*this == other);
}
     //// Operator<<
        //// Base 1
std::ostream& operator<<(std::ostream& os, const FlappyBus& flappyBus) {
    os << "Nome: " << flappyBus.playerName << std::endl;
    os << "Posicao: " << flappyBus.position << std::endl;
    os << "Velocidade: " << flappyBus.velocity << std::endl;
    os << "Pontuacao: " << flappyBus.score << std::endl;
    os << "Pontuacao maxima: " << flappyBus.scoreManager.getMaxScore() << std::endl;
    return os;
}
            ////Derivadas da Base 1 - mostrar uso static_cast
std::ostream& operator<<(std::ostream& os, const Vehicle& vehicle) {
    // Usa a sobrecarga da classe base (FlappyBus)
    os << static_cast<const FlappyBus&>(vehicle);

    os << "Capacidade de combustivel: " << vehicle.fuelCapacity << " litros\n";
    os << "Tipo de combustivel: " << vehicle.fuelType << "\n";

    return os;
}

std::ostream& operator<<(std::ostream& os, const SpaceBus& spaceBus) {
    // Usa a sobrecarga da classe base (FlappyBus)
    os << static_cast<const FlappyBus&>(spaceBus);

    os << "Tipo de Propulsao: " << spaceBus.propulsionType << "\n";

    return os;
}
        //// Base 2
std::ostream& operator<<(std::ostream& os, const Vehicle& vehicle) {
    // Usa a sobrecarga da classe base (FlappyBus)
    os << static_cast<const FlappyBus&>(vehicle);

    os << "Capacidade de combustivel: " << vehicle.fuelCapacity << " litros\n";
    os << "Tipo de combustivel: " << vehicle.fuelType << "\n";

    return os;
}
            ////Derivadas da Base 2 - mostrar uso static_cast
std::ostream& operator<<(std::ostream& os, const SportsCar& sportsCar) {
    // Usa a sobrecarga da classe base (Vehicle)
    os << static_cast<const Vehicle&>(sportsCar);

    os << "Carro esportivo\n";
    os << "Turbo: " << (sportsCar.turbo ? "ativado" : "desativado") << "\n";

    return os;
}

std::ostream& operator<<(std::ostream& os, const ElectricCar& electricCar) {
    // Usa a sobrecarga da classe base (Vehicle)
    os << static_cast<const Vehicle&>(electricCar);

    os << "Capacidade da bateria: " << electricCar.batteryCapacity << " kWh\n";
    os << "Tipo de conector: " << electricCar.connectorType << "\n";

    return os;
}

//// Para cada classe do seu projeto criar pelo menos dois constructores, 
 //sendo um o constructor de cópia 
 ////Mostrar uso de reaproveitamento de código da base na derivada

    //// Base 1 - constructores
        ////Constructor 1
FlappyBus::FlappyBus(): position(5), velocity(3), score(0), playerName("Player"), eventLog(nullptr), eventLogSize(0), eventCount(0) {}

FlappyBus::FlappyBus(int initialPosition, double initialVelocity, const std::string& name): position(initialPosition), velocity(initialVelocity), score(0), playerName(name), eventLog(nullptr), eventLogSize(0), eventCount(0){}

        ////Constructor de cópia
FlappyBus::FlappyBus(const FlappyBus &c_flappyBus){
    this->playerName = c_flappyBus.playerName;
    this->position = c_flappyBus.position;
    this->velocity = c_flappyBus.velocity;
    this-> score = c_flappyBus.score;

     // Copiar o registro de eventos do jogo
    this->eventLogSize = c_flappyBus.eventLogSize;
    this->eventCount = c_flappyBus.eventCount;
    this->eventLog = new std::string[this->eventLogSize];
    for (int i = 0; i < eventCount; ++i) {
        this->eventLog[i] = c_flappyBus.eventLog[i];
    }
};
    //// Base 2 - constructores
        ////Constructor 1
Vehicle::Vehicle(): FlappyBus(){
    this->setFuelCapacity(100);
    this->setfuelType("Gasolina");
}

Vehicle::Vehicle(int initialPosition, double initialVelocity, const std::string& name, int fuelCapacity, const std::string& fuelType): FlappyBus(initialPosition, initialVelocity, name), fuelType(fuelType) {
    this->setFuelCapacity(fuelCapacity);
    this->setfuelType(fuelType);
}

        ////Constructor de cópia
Vehicle::Vehicle(const Vehicle& other) : FlappyBus(other) {
    this->fuelCapacity = other.fuelCapacity;
    this->fuelType = other.fuelType;
}

    //// Base 3 - constructores
        ////Constructor 1
SpaceBus::SpaceBus() : FlappyBus(), propulsionType("Unknown"), hatchOpen(false), environmentalTemperature(22.0), environmentalPressure(1.0), environmentalOxygenLevel(20.9), destination("Undefined") {}

SpaceBus::SpaceBus(int initialPosition, double initialVelocity, const std::string& name, const std::string& propulsionType): FlappyBus(initialPosition, initialVelocity, name), propulsionType(propulsionType), hatchOpen(false), environmentalTemperature(22.0), environmentalPressure(1.0), environmentalOxygenLevel(20.9), destination("Undefined") {}

        ////Constructor de cópia 
SpaceBus::SpaceBus(const SpaceBus& other) : FlappyBus(other), propulsionType(other.propulsionType), hatchOpen(other.hatchOpen), environmentalTemperature(other.environmentalTemperature), environmentalPressure(other.environmentalPressure), environmentalOxygenLevel(other.environmentalOxygenLevel), destination(other.destination) {}

    ////Derivadas - constructores

        //// Hierarquia 1

             ////Classe 1
                 ////Constructor 1
FlappyBus::FlappyBus(): position(5), velocity(3), score(0), playerName("Player"), eventLog(nullptr), eventLogSize(0), eventCount(0) {}

FlappyBus::FlappyBus(int initialPosition, double initialVelocity, const std::string& name): position(initialPosition), velocity(initialVelocity), score(0), playerName(name), eventLog(nullptr), eventLogSize(0), eventCount(0){}

                 ////Constructor de cópia
FlappyBus::FlappyBus(const FlappyBus &c_flappyBus){
    this->playerName = c_flappyBus.playerName;
    this->position = c_flappyBus.position;
    this->velocity = c_flappyBus.velocity;
    this-> score = c_flappyBus.score;

     // Copiar o registro de eventos do jogo
    this->eventLogSize = c_flappyBus.eventLogSize;
    this->eventCount = c_flappyBus.eventCount;
    this->eventLog = new std::string[this->eventLogSize];
    for (int i = 0; i < eventCount; ++i) {
        this->eventLog[i] = c_flappyBus.eventLog[i];
    }
};
             ////Classe 2
                 ////Constructor 1
Vehicle::Vehicle(): FlappyBus(){
    this->setFuelCapacity(100);
    this->setfuelType("Gasolina");
}

Vehicle::Vehicle(int initialPosition, double initialVelocity, const std::string& name, int fuelCapacity, const std::string& fuelType): FlappyBus(initialPosition, initialVelocity, name), fuelType(fuelType) {
    this->setFuelCapacity(fuelCapacity);
    this->setfuelType(fuelType);
}

                 ////Constructor de cópia
Vehicle::Vehicle(const Vehicle& other) : FlappyBus(other) {
    this->fuelCapacity = other.fuelCapacity;
    this->fuelType = other.fuelType;
}
            
             ////Classe 3
                 ////Constructor 1
SpaceBus::SpaceBus() : FlappyBus(), propulsionType("Unknown"), hatchOpen(false), environmentalTemperature(22.0), environmentalPressure(1.0), environmentalOxygenLevel(20.9), destination("Undefined") {}

SpaceBus::SpaceBus(int initialPosition, double initialVelocity, const std::string& name, const std::string& propulsionType): FlappyBus(initialPosition, initialVelocity, name), propulsionType(propulsionType), hatchOpen(false), environmentalTemperature(22.0), environmentalPressure(1.0), environmentalOxygenLevel(20.9), destination("Undefined") {}

                 ////Constructor de cópia
SpaceBus::SpaceBus(const SpaceBus& other) : FlappyBus(other), propulsionType(other.propulsionType), hatchOpen(other.hatchOpen), environmentalTemperature(other.environmentalTemperature), environmentalPressure(other.environmentalPressure), environmentalOxygenLevel(other.environmentalOxygenLevel), destination(other.destination) {}

        //// Hierarquia 2

             ////Classe 1
                 ////Constructor 1
SportsCar::SportsCar() : Vehicle(), turbo(false) {}

SportsCar::SportsCar(int initialPosition, double initialVelocity, const std::string& name, int fuelCapacity, const std::string& fuelType, bool turbo)
    : Vehicle(initialPosition, initialVelocity, name, fuelCapacity, fuelType), turbo(turbo) {
}

                 ////Constructor de cópia
SportsCar::SportsCar(const SportsCar& other) : Vehicle(other), turbo(other.turbo) {}

             ////Classe 2
                 ////Constructor 1
ElectricCar::ElectricCar() : Vehicle(), batteryCapacity(0), connectorType("Type 2") {}

ElectricCar::ElectricCar(int initialPosition, double initialVelocity, const std::string& name, int fuelCapacity, int batteryCapacity, const std::string& connectorType)
    : Vehicle(initialPosition, initialVelocity, name, fuelCapacity, fuelTypeElectric), batteryCapacity(batteryCapacity), connectorType(connectorType) {}

                 ////Constructor de cópia
ElectricCar::ElectricCar(const ElectricCar& other) : Vehicle(other), batteryCapacity(other.batteryCapacity), connectorType(other.connectorType) {}

//// Carregamento e salvamento de arquivos
    /*É necessário ter a funcionalidade: 1. 
      leitura de arquivos para configuração das suas classes e variáveis de status, 2. 
      processamento das variáveis de status e 3. salvamento dessas variáveis. 
      Sem o diagrama UML, a saída do programa e o vídeo, o trabalho não será avaliado.*/

    //Link arquivo de configuração no repositório
        https://github.com/Jp0liveira/Flappy-Bus/tree/desenvolvimento

    //Link vídeo mostrando a execução do código usando o arquivo de configuração
        https://drive.google.com/file/d/1ostTRylKfoqzqLkdDOLSHdg1xZTEEFda/view?usp=sharing
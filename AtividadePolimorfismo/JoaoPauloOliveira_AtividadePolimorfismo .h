/*
Expandir a hierarquia da atividade anterior: três hierarquias de três níveis.
    Sendo que em uma das hierarquias há dois níveis de classes 
    abstratas. Uma das classes abstratas precisa ter pelo menos dois métodos virtuais 
    puros. 

    Para cada lado da hierarquia criar ao menos duas classes concretas. 
        Pelo menos duas classes concretas herdando de uma dessas outras classes 
        concretas. 
        Cada classe, além dos métodos herdados, precisa ter pelo menos um método que tenha 
        alguma funcionalidade, que não seja set e get. 

Para cada classe do seu projeto criar pelo menos três constructores, sendo um o 
constructor de cópia. 
 
Em uma das hierarquias deve haver alocação de memória usando um vector< ptr * >, 
onde ptr é  um ponteiro de uma de suas classes criadas que tem relação de composição. 
 
Ter um atributo static e um atributo const static.  

Fazer a sobrecarga para cada classe dos operadores =, ==, ≠, ! e << (friend) para as 
classes concretas. Usar sempre que possível o static_cast para reaproveitamento de código - mas não é possível usar
para classes abstract.  
 
Criar um vector de ponteiros de uma das classes abstrata e  armazenar nele objetos 
de classes concretas. Usar dynamic_cast e typeid para fazer algo significativo com 
partes dessas classes concretas. 
 
Carregamento e salvamento de  arquivos: é necessário ter a funcionalidade de 
 1. leitura de arquivos para  configuração das suas classes e variáveis de status, 
 2. processamento das variáveis de status e 
 3. salvamento dessas variáveis. 
 
Todos os projetos devem ter um diagrama mostrando a hierarquia. 
Sem o diagrama e os dois videos, o trabalho não será avaliado.*/


//// Geral - parte para revisão
    //Diagrama UML    
    //Organização do código 

////Importante
//// Cada classe, além dos métodos herdados, precisa ter pelo menos um método que tenha 
//alguma funcionalidade, que não seja set e get.

//// Os .h

    /// O .h das classes bases

        //Classe abstract base 1    
        #pragma once
#include "FlappyBus.h"

enum ObstacleType {
    BLOCK,
    HOUSE,
    TREE,
    ROCK,
    CLOUD,
    MOUNTAIN,
    BRIDGE,
    BUSH,
    FENCE,
    TOWER,
    FLOATINGOBSTACLE,
};

class ObstacleCharacter : public FlappyBus {

    public:
        ObstacleCharacter(); 
        ObstacleCharacter(int initialPosition, double initialVelocity, ObstacleType obstacleType);
        ObstacleCharacter(const ObstacleCharacter& other); 
        virtual ~ObstacleCharacter();

        // // Métodos puros
        virtual void collide() = 0;   // Método chamado quando ocorre uma colisão
        virtual void moveDown() = 0;  // Método chamado para movimentação descendente do obstáculo

        std::string getObstacleTypeName() const;  // Retorna o nome legível do tipo de obstáculo

    protected:
        ObstacleType obstacleType;
};

        //Classe abstract base 2
        #pragma once
#include "ObstacleCharacter.h"

class FloatingObstacle : public ObstacleCharacter {
    public:
        FloatingObstacle(); 
        FloatingObstacle(int initialPosition, double initialVelocity);
        FloatingObstacle(const FloatingObstacle& other);
        virtual ~FloatingObstacle(); 
        
        void collide() override;
        void moveDown() override;

        //  Métodos virtuais puros
        virtual void floatInAir() = 0;   // Método específico para obstáculos flutuantes
        virtual void applyWindForce() = 0;  // Método para aplicar força de vento

};
    /// O .h da hierarquia 1 (abstract base 1)

        //Classe Abstract 1 que herda da base abstract
            //Deve ter seu próprio método virtual puro
#pragma once
#include "ObstacleCharacter.h"

class FloatingObstacle : public ObstacleCharacter {
    public:
        FloatingObstacle(); 
        FloatingObstacle(int initialPosition, double initialVelocity);
        FloatingObstacle(const FloatingObstacle& other);
        virtual ~FloatingObstacle(); 
        
        void collide() override;
        void moveDown() override;

        //  Métodos virtuais puros
        virtual void floatInAir() = 0;   // Método específico para obstáculos flutuantes
        virtual void applyWindForce() = 0;  // Método para aplicar força de vento

};
        //Classe 2 - concrete
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

        double setGasLevel(double newGasLevel);
        static const double defaultMaxGasLevel;  // Valor máximo padrão para gasLevel
        static const double minGasLevel;         // Valor mínimo permitido para gasLevel
        static double maxGasLevel;               // Valor máximo permitido para gasLevel

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
        //Classe 3 - concrete
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

         //Classe 4 - concrete
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

    /// O .h da hierarquia 2 (abstract base 2)

        //Classe 1 (abstract or concrete)
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

        //Classe 2
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

    /// O .h da hierarquia 3 (abstract base 3)

        //Classe 1
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

        //Classe 2
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


////Implementação de constructores default de cópia

    ///Bases abstract

        //Classe abstract base 1    
ObstacleCharacter::ObstacleCharacter(): FlappyBus(), obstacleType(BLOCK){}

ObstacleCharacter::ObstacleCharacter(int initialPosition, double initialVelocity, ObstacleType obstacleType): FlappyBus(initialPosition, initialVelocity, "Obstacle"), obstacleType(obstacleType) {}

ObstacleCharacter::ObstacleCharacter(const ObstacleCharacter& other): FlappyBus(other), obstacleType(other.obstacleType) {}

ObstacleCharacter::~ObstacleCharacter() {}

        //Classe abstract base 2
FloatingObstacle::FloatingObstacle() : ObstacleCharacter() {
    ObstacleCharacter::obstacleType = ObstacleType::FLOATINGOBSTACLE;
}

FloatingObstacle::FloatingObstacle(int initialPosition, double initialVelocity)
    : ObstacleCharacter(initialPosition, initialVelocity, ObstacleType::FLOATINGOBSTACLE) {}

FloatingObstacle::FloatingObstacle(const FloatingObstacle& other): ObstacleCharacter(other) {}

FloatingObstacle::~FloatingObstacle() {}

    ////Classes concretas - mostrar reaproveitamento de código

        /// Hierarquia 1 (abstract base 1)

            //Classe Abstract 1 que herda da base abstract
FloatingObstacle::FloatingObstacle() : ObstacleCharacter() {
    ObstacleCharacter::obstacleType = ObstacleType::FLOATINGOBSTACLE;
}

FloatingObstacle::FloatingObstacle(int initialPosition, double initialVelocity)
    : ObstacleCharacter(initialPosition, initialVelocity, ObstacleType::FLOATINGOBSTACLE) {}

FloatingObstacle::FloatingObstacle(const FloatingObstacle& other): ObstacleCharacter(other) {}

FloatingObstacle::~FloatingObstacle() {}   

            //Classe 2 - concrete
HotAirBalloon::HotAirBalloon() : FloatingObstacle(), gasLevel(maxGasLevel) {}

HotAirBalloon::HotAirBalloon(int initialPosition, double initialVelocity)
    : FloatingObstacle(initialPosition, initialVelocity), gasLevel(maxGasLevel) {}

HotAirBalloon::HotAirBalloon(const HotAirBalloon& other)
    : FloatingObstacle(other), gasLevel(other.gasLevel) {}

HotAirBalloon::~HotAirBalloon() {}

            //Classe 3 - concrete
FireBalloon::FireBalloon(): HotAirBalloon(),  FireControl() {}

FireBalloon::FireBalloon(int initialPosition, double initialVelocity): HotAirBalloon(initialPosition, initialVelocity), FireControl() {}

FireBalloon::FireBalloon(const FireBalloon& other): HotAirBalloon(other), FireControl(other) {}

FireBalloon::~FireBalloon() {}

            //Classe 4 - concrete
WaterBalloon::WaterBalloon(): HotAirBalloon(), WaterControl(){}

WaterBalloon::WaterBalloon(int initialPosition, double initialVelocity): HotAirBalloon(initialPosition, initialVelocity), WaterControl() {}

WaterBalloon::WaterBalloon(const WaterBalloon& other): HotAirBalloon(other), WaterControl(other) {}

WaterBalloon::~WaterBalloon() {}

//// Mostrar implementação dos métodos virtuais puros nas classes concretas
 /// Mostrar reaproveitamente de código da base

    /// Hierarquia 1
         //Base - métodos virtuais puros
class FloatingObstacle : public ObstacleCharacter {
    public:
        virtual void floatInAir() = 0;   // Método específico para obstáculos flutuantes
        virtual void applyWindForce() = 0;  // Método para aplicar força de vento
}
         //Classe concrete 1
class HotAirBalloon : public FloatingObstacle {
    public:
        void floatInAir() override;
        void applyWindForce() override;      
}
void HotAirBalloon::floatInAir() {
    // Implementação específica para flutuar no ar (herdado de FloatingObstacle)
    std::cout << "HotAirBalloon floating in the air!" << std::endl;
}

void HotAirBalloon::applyWindForce() {
    // Implementação específica para aplicar força de vento (herdado de FloatingObstacle)
    std::cout << "HotAirBalloon applying wind force!" << std::endl;
}

    /// Hierarquia 2

         //Base - métodos virtuais puros
class FireControl {
    public:
        virtual void ignite() = 0;  // Método para iniciar o fogo
        virtual void extinguish() = 0;  // Método para apagar o fogo
        // Descrição do controle de fogo
        virtual std::string getDescription() const = 0;
};
         //Classe concrete 1
class FireBalloon : public HotAirBalloon, public FireControl {
    public:
        void ignite() override;
        void extinguish() override;
        std::string getDescription() const override;

}

void FireBalloon::ignite() {
    // Implementação específica para iniciar o fogo (herdado de FireControl)
    std::cout << "FireBalloon igniting fire!" << std::endl;
    isOnFire = true;
}

void FireBalloon::extinguish() {
    // Implementação específica para apagar o fogo (herdado de FireControl)
    std::cout << "FireBalloon extinguishing fire!" << std::endl;
    isOnFire = false;
}

std::string FireBalloon::getDescription() const {
    // Descrição específica para FireBalloon
    return isOnFire ? "FireBalloon with fire control (On Fire)" : "FireBalloon with fire control (Not On Fire)";
}

    /// Hierarquia 3

         //Base - métodos virtuais puros
class WaterControl {
    public:
        virtual void fill() = 0;  // Método para encher o balão com água
        virtual void release() = 0;  // Método para liberar água do balão
        // Descrição do controle de água
        virtual std::string getDescription() const = 0;
};
         //Classe concrete 1
class WaterBalloon : public HotAirBalloon, public WaterControl {
    public:
        void fill() override;
        void release() override;
        std::string getDescription() const override;   

}

void WaterBalloon::fill() {
    // Implementação específica para encher o balão com água
    std::cout << "WaterBalloon filling with water!" << std::endl;
}

void WaterBalloon::release() {
    // Implementação específica para liberar água do balão
    std::cout << "WaterBalloon releasing water!" << std::endl;
}

std::string WaterBalloon::getDescription() const {
    // Descrição específica para WaterBalloon
    return "WaterBalloon with water control";
}


//// Em uma das hierarquias deve haver alocação de memória usando um vector< ptr * >, 
// onde ptr é um ponteiro de uma de
//suas classes criadas que tem relação de composição.

    /// Mostrar .h com este vector (com apenas ele presente) usando "..." para omitir
    //o resto
#pragma once
#include "HotAirBalloon.h"
#include <vector>
class BalloonPlayset {
    private:
        std::vector<HotAirBalloon*> balloons;
};

    /// Mostrar inicialização do vector 
void BalloonPlayset::addBalloon(HotAirBalloon* balloon) {
    balloons.push_back(balloon);
}

    /// Mostrar o método que aplica new nele
int main() {
   
    // Criando instâncias de balões
    HotAirBalloon* hotAirBalloon = new HotAirBalloon();
    FireBalloon* fireBalloon = new FireBalloon(1, 10.0);
    WaterBalloon* waterBalloon = new WaterBalloon(2, 8.0);

    // Criando uma instância de BalloonPlayset
    BalloonPlayset balloonPlayset;

    // Adicionando balões ao conjunto de obstaculos
    balloonPlayset.addBalloon(hotAirBalloon);
    balloonPlayset.addBalloon(fireBalloon);
    balloonPlayset.addBalloon(waterBalloon);

    // Simulando os obstaculos com os balões
    balloonPlayset.playWithBalloons();

    // Liberando a memória alocada
    delete hotAirBalloon;
    delete fireBalloon;
    delete waterBalloon;
    
    return 0;

}
    /// Mostrar método em que ele é usado efetivamente
    //preenchimento, set e get serão ignorados

void BalloonPlayset::playWithBalloons() {
    for (auto balloon : balloons) {
        
        balloon->floatInAir();
        balloon->applyWindForce();

        // verifica se realmente é um tipo FireBalloon
        FireBalloon* fireBalloon = dynamic_cast<FireBalloon*>(balloon);
        if (fireBalloon) {
            fireBalloon->ignite();
        }

        // verifica se realmente é um tipo WaterBalloon
        WaterBalloon* waterBalloon = dynamic_cast<WaterBalloon*>(balloon);
        if (waterBalloon) {
            waterBalloon->fill();
        }
    }
}
    ///Mostrar destructor e desalocação
BalloonPlayset::~BalloonPlayset() {
    for (auto balloon : balloons) {
        delete balloon;
    }
}
    /// Mostrar o uso (indireto) deste vector


//// Ter um atributo static e um atributo const static.

    /// .h mostrando apenas eles e o método que os manipula
#pragma once
#include "FloatingObstacle.h"

class HotAirBalloon : public FloatingObstacle {
    public:
        double setGasLevel(double newGasLevel);
        static const double defaultMaxGasLevel;  // Valor máximo padrão para gasLevel
        static const double minGasLevel;         // Valor mínimo permitido para gasLevel
        static double maxGasLevel;               // Valor máximo permitido para gasLevel

};

    /// Inicialização no .cpp
#include "HotAirBalloon.h"

const double HotAirBalloon::defaultMaxGasLevel = 100.0; // Valor máximo padrão
const double HotAirBalloon::minGasLevel = 0.0; // Valor mínimo permitido
double HotAirBalloon::maxGasLevel = HotAirBalloon::defaultMaxGasLevel; // Inicializa com o valor padrão

    /// Mostra método(s) em que são usados efetivamente

HotAirBalloon::HotAirBalloon() : FloatingObstacle(), gasLevel(maxGasLevel) {}

HotAirBalloon::HotAirBalloon(int initialPosition, double initialVelocity)
    : FloatingObstacle(initialPosition, initialVelocity), gasLevel(maxGasLevel) {}
    
double HotAirBalloon::setGasLevel(double newGasLevel) {
    // Verifica se o novo nível de gás está dentro dos limites
    if (newGasLevel >= minGasLevel && newGasLevel <= maxGasLevel) {
        gasLevel = newGasLevel;
    } else {
        gasLevel = minGasLevel;
    }
    return gasLevel;
}

bool HotAirBalloon::processVariables(const std::map<std::string, double>& numericVariables, const std::map<std::string, std::string>& stringVariables, const std::map<std::string, bool>& boolVariables) {
    if (numericVariables.find("initialPosition") != numericVariables.end())
        setPosition(numericVariables.at("initialPosition"));

    if (numericVariables.find("initialVelocity") != numericVariables.end())
        setVelocity(numericVariables.at("initialVelocity"));

    if (stringVariables.find("name") != stringVariables.end())
        setPlayerName(stringVariables.at("name"));

    if (numericVariables.find("gasLevel") != numericVariables.end())
        this->gasLevel = this->setGasLevel(numericVariables.at("gasLevel"));

    return true;
}

//// Fazer a sobrecarga para todas as classes dos operadores =, ==, ≠ e << (friend)

//Base abstract
const Entity &Entity::operator=(const Entity &assigned_entity) {
    if (this != &assigned_entity) {
        this->name = assigned_entity.name;
        this->age = assigned_entity.age;

        ...

        // primeiro limpa o vetor para preenche-lo
        for (auto sword : this->inventory.swords) {
            delete sword;
        }
        ...
    }

    return *this; // permite a forma a = b = c
}


//Class concrete
const Human &Human::operator=(const Human &other_human) {
    if (this != &other_human) {
        // forma não permitida pela classe abstrata
        //*static_cast< Entity * >( this ) = static_cast< Entity >( other_human );
        Entity::operator=(other_human);
        if (other_human.equipped.steel_sword == 0) equipped.steel_sword = 0;
        else equipped.steel_sword = new Sword(*other_human.equipped.steel_sword);

        ...
        
    }
    return *this;
}

     /// Operator=
        /// Hierarquia 1
             //Base

             //Derivadas da Base 1 - mostrar uso static_cast

             //Derivadas da Derivada - mostrar uso static_cast

             //e assim por diante

        /// Hierarquia 2
             //Base

             //Derivadas da Base 2 - mostrar uso static_cast

             //Derivadas da Derivada - mostrar uso static_cast

             //e assim por diante


        /// Hierarquia 3
             //Base

             //Derivadas da Base 3 - mostrar uso static_cast

             //Derivadas da Derivada - mostrar uso static_cast

             //e assim por diante



     //// Operators== e !=
         // Hierarquia 1
             //Base

             //Derivadas da Base 1 - mostrar uso static_cast

             //Derivadas da Derivada - mostrar uso static_cast

             //e assim por diante


         //// Hierarquia 2
             //Base

             //Derivadas da Base 2 - mostrar uso static_cast

             //Derivadas da Derivada - mostrar uso static_cast

             //e assim por diante


        //// Hierarquia 3
             //Base

             //Derivadas da Base 3 - mostrar uso static_cast

             //Derivadas da Derivada - mostrar uso static_cast

             //e assim por diante


     //// Operator<<
        //// Hierarquia 1
             //Base

             //Derivadas da Base 1 - mostrar uso static_cast

              //Derivadas da Derivada - mostrar uso static_cast

             //e assim por diante


        //// Hierarquia 2
             //Base

             //Derivadas da Base 2 - mostrar uso static_cast

              //Derivadas da Derivada - mostrar uso static_cast

             //e assim por diante


       //// Hierarquia 3

             //Base

             //Derivadas da Base 3 - mostrar uso static_cast

              //Derivadas da Derivada - mostrar uso static_cast

             //e assim por diante

            

//// Carregamento e salvamento de arquivos
    /*É necessário ter a funcionalidade: 1. 
      leitura de arquivos para configuração das suas classes e variáveis de status, 
      2. processamento das variáveis de status e 
      3. salvamento dessas variáveis. 
      
///Sem o diagrama UML, a saída do programa e o vídeo, o trabalho não será avaliado.*/

    //Link arquivo de configuração no repositório

    //Link vídeo mostrando a execução do código usando o arquivo de configuração
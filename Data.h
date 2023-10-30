#ifndef DATA_H
#define DATA_H

class Data {
public:
    Data(int = 1, int = 1, int = 1900);
    void print() const;
    void setCurrentDate(); // Define a data e hora atual

private:
    int mes;
    int dia;
    int ano;
    int hora;
    int minuto;
    int segundo;

    int VerificaDia(int) const;
};

#endif // DATA_H

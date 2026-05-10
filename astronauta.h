#ifndef ASTRONAUTA_H
#define ASTRONAUTA_H

#include <string>

using namespace std;

class Astronautas {
public:
    string cpf;
    int idade;
    string nome;
    bool esta_vivo = true;
    bool esta_disponivel = true;

    Astronautas(string c, int i, string n);
};

#endif
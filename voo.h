#ifndef VOO_H
#define VOO_H

#include <vector>
#include <string>

using namespace std;

enum est_voo {
    PLANEJADO,
    EM_CURSO,
    FINALIZADO_S,
    FINALIZADO_EX
};

class Voo {
public:
    int codigo_voo;
    vector<string> astronautas_cpf;
    est_voo estado_voo = PLANEJADO;

    Voo(int cod);

    bool tem_astro_voo(string cpf);
};

#endif
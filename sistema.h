#ifndef SISTEMA_H
#define SISTEMA_H

#include <vector>
#include <string>
#include "astronauta.h"
#include "voo.h"

using namespace std;

class Sistema {
public:
    vector<Astronautas> astronautas;
    vector<Voo> voos;

    bool tem_cpf(string c);
    bool tem_voo(int cod);

    Astronautas* buscarAstronauta(string cpf);
    Voo* buscarVoo(int cod);

    void cadastrar_astronauta(string c, int i, string n);
    void cadastrar_voo(int cod);

    void adicionar_astronauta_voo(string cpf, int cod_voo);
    void remover_astronauta_voo(string cpf, int cod_voo);
    void lancar_voo(int cod_voo);
    void explodir_voo(int cod_voo);
    void finalizar_voo(int cod_voo);

    string listar_astro_mortos();
    string listar_detalhes_voo(est_voo est);
    string listar_voos();
};

#endif

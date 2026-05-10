#include <iostream>
#include <fstream>
#include <sstream>
#include "sistema.h"

using namespace std;

#define ARQUIVO_ENTRADA_PADRAO "comandos.txt"

int main(){
    Sistema sistema;

    ifstream arquivo(ARQUIVO_ENTRADA_PADRAO);
    string comando;

    if (arquivo.is_open()) {
        while (getline(arquivo, comando)) {
            cout << comando << endl;

            istringstream iss(comando);
            string operacao;
            iss >> operacao;

            if (operacao == "FIM") break;

            if (operacao == "CADASTRAR_ASTRONAUTA") {
                string cpf, nome;
                int idade;
                iss >> cpf >> idade;
                getline(iss, nome);
                sistema.cadastrar_astronauta(cpf, idade, nome);
            }

            if (operacao == "CADASTRAR_VOO") {
                int cod_voo;
                iss >> cod_voo;
                sistema.cadastrar_voo(cod_voo);
            }

            if (operacao == "ADICIONAR_ASTRONAUTA") {
                string cpf;
                int cod_voo;
                iss >> cpf >> cod_voo;
                sistema.adicionar_astronauta_voo(cpf, cod_voo);
            }

            if (operacao == "REMOVER_ASTRONAUTA") {
                string cpf;
                int cod;
                iss >> cpf >> cod;
                sistema.remover_astronauta_voo(cpf, cod);
            }

            if (operacao == "LANCAR_VOO") {
                int cod_voo;
                iss >> cod_voo;
                sistema.lancar_voo(cod_voo);
            }

            if (operacao == "EXPLODIR_VOO") {
                int cod_voo;
                iss >> cod_voo;
                sistema.explodir_voo(cod_voo);
            }

            if (operacao == "FINALIZAR_VOO") {
                int cod_voo;
                iss >> cod_voo;
                sistema.finalizar_voo(cod_voo);
            }

            if (operacao == "LISTAR_MORTOS") {
                cout << sistema.listar_astro_mortos() << endl;
            }

            if (operacao == "LISTAR_VOOS") {
                cout << sistema.listar_voos() << endl;
            }
        }

        arquivo.close();
    } else {
        cout << "Erro ao abrir o arquivo." << endl;
    }

    return 0;
}
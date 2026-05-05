#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

// constantes
#define ARQUIVO_ENTRADA_PADRAO    "comandos.txt"

// listas para guardar dados (declarar antes das classes)
vector<class Astronautas> V_ASTRONAUTAS;
vector<class Voo> V_VOOS;

// funções utilitárias
bool tem_cpf(string cA);

enum est_voo {
    PLANEJADO,
    EM_CURSO,
    FINALIZADO_S,
    FINALIZADO_EX
};

// classes importantes
class Astronautas {
public:
    string cpf;
    int idade;
    string nome;
    bool esta_vivo = true;
    bool esta_disponivel = true;

    Astronautas(string c, int i, string n){
        cpf = c;
        idade = i;
        nome = n;
    }

    static void cadastrar_astronauta(string c, int i, string n){
        if (tem_cpf(c) == false) 
        {
            V_ASTRONAUTAS.push_back(Astronautas(c, i, n));
        } else {
            cout << "O CPF " << c <<" já está cadastrado. Abortando admissão." << endl;
        }
    };
};

class Voo {
public:
    int codigo_voo;
    vector <string> astronautas_cpf;
    enum est_voo estado_voo;
};

int main(){
    ifstream arquivo(ARQUIVO_ENTRADA_PADRAO);
    string comando;

    if (arquivo.is_open()) {
        while (getline(arquivo, comando)) {
            cout << comando << endl; 

            // Extrai a primeira palavra do comando
            istringstream iss(comando);
            string operacao;
            iss >> operacao;

            if (operacao == "FIM") {
                break;
            }

            if (operacao == "CADASTRAR_ASTRONAUTA") {
                string cpf, nome;
                int idade;
                iss >> cpf >> idade;
                getline(iss, nome);
                Astronautas::cadastrar_astronauta(cpf, idade, nome);
            }
        }

        arquivo.close();
    } else {
        cout << "Erro ao abrir o arquivo." << endl;
    }

    return 0;
};

bool tem_cpf(string cA){
    if (V_ASTRONAUTAS.empty())
    {
        return false;
    }
    
    for (Astronautas ast: V_ASTRONAUTAS)
    {
        if (ast.cpf.compare(cA) == 0)
        {
            return true;
        }
    }

    return false;
};
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

// constantes
#define ARQUIVO_ENTRADA_PADRAO    "comandos.txt"

// listas para guardar dados (declarar antes das classes)
vector<class Astronautas> V_ASTRONAUTAS;
vector<class Voo> V_VOOS;

// funções utilitárias

// saber se tem ou não astronauta cadastrado
bool tem_cpf(string cA);
// saber se tem ou não voo cadastrado
bool tem_voo(int cod);

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

    static Astronautas* recuperar_astronauta_cpf(string c){
        for (Astronautas &ast: V_ASTRONAUTAS)
        {
            if (ast.cpf.compare(c) == 0)
            {
                return &ast;
            }
        }
        cout << "Não foi encontrado nenhum astronauta com esse código." << endl;
        return nullptr;
    }

};

class Voo {
public:
    int codigo_voo;
    vector <string> astronautas_cpf;
    enum est_voo estado_voo = PLANEJADO;

    Voo(int cod){
        codigo_voo = cod;
    }

    bool tem_astro_voo(string cpf){
        if (astronautas_cpf.empty())
        {
            return false;
        }
        
        for (string c: astronautas_cpf)
        {
            if (c.compare(cpf) == 0)
            {
                return true;
            }
        }

        return false;
    }

    static Voo* recuperar_voo_cod(int cod){
        for (Voo &v: V_VOOS)
        {
            if (v.codigo_voo == cod)
            {
                return &v;
            }
        }
        cout << "Não foi encontrado nenhum voo com esse código." << endl;

        return nullptr;
    }

    static void cadastrar_voo(int cod){
        if (tem_voo(cod) == false)
        {
            V_VOOS.push_back(Voo(cod));
        } else {
            cout << "O código de voo " << cod <<" já está cadastrado. Abortando admissão." << endl;
        }
    }

    static void adicionar_astronauta_voo(string cpf, int cod_voo){
        if (tem_cpf(cpf) && tem_voo(cod_voo) == true)
        {
            Astronautas* ast = Astronautas::recuperar_astronauta_cpf(cpf);
            Voo* voo = Voo::recuperar_voo_cod(cod_voo);

            if (voo != nullptr && voo->estado_voo == PLANEJADO && ast->esta_vivo == true 
                && voo->tem_astro_voo(cpf) == false)
            {
                voo->astronautas_cpf.push_back(cpf);
            } else {
                cout << "Por causas adversas, não foi possível realizar esta ação. ";
                cout << "Verifique o estado do voo, astronautas ou a lista de passageiros." << endl;
            }
        } else {
            cout << "Não foi possível encontrar o astronauta/voo selecionado." << endl;
        }
    }

    static void remover_astronauta_voo(string cpf, int cod_voo){
        if (tem_cpf(cpf) && tem_voo(cod_voo) == true)
        {
            Voo* voo = Voo::recuperar_voo_cod(cod_voo);
            
            if (voo != nullptr && voo->estado_voo == PLANEJADO
                && voo->tem_astro_voo(cpf) == true)
            {   
                voo->astronautas_cpf.erase(
                    remove(voo->astronautas_cpf.begin(), voo->astronautas_cpf.end(), cpf),
                    voo->astronautas_cpf.end()
                );
            } else {
                cout << "Por causas adversas, não foi possível realizar esta ação. ";
                cout << "Verifique o estado do voo ou a lista de passageiros." << endl;
            }
        } else {
            cout << "Não foi possível encontrar o astronauta/voo selecionado." << endl;
        }
    }

    static void lancar_voo(int cod_voo){
        if (tem_voo(cod_voo) == true)
        {
            Voo* voo = Voo::recuperar_voo_cod(cod_voo);

            if (voo != nullptr && voo->estado_voo == PLANEJADO
                && voo->astronautas_cpf.empty() == false)
            {   
                bool todos_disp = true;
                for (string ast_v: voo->astronautas_cpf)
                {
                    Astronautas* ast = Astronautas::recuperar_astronauta_cpf(ast_v);
                    if (ast->esta_disponivel == false || ast->esta_vivo == false){
                        todos_disp = false;
                        cout << "O astronauta de cpf:" << ast_v << " não poderá participar do lançamento." << endl;
                        cout << "Abortando missão..." << endl;
                        break;
                    }
                }

                if (todos_disp == true)
                {
                    voo->estado_voo = EM_CURSO;

                    for (string ast_v: voo->astronautas_cpf)
                    {
                        Astronautas* ast = Astronautas::recuperar_astronauta_cpf(ast_v);
                        ast->esta_disponivel = false;
                    }
                }
            } else {
                cout << "Por causas adversas, não foi possível realizar esta ação.";
                cout << "verifique o estado do voo ou se há algum passageiro." << endl;
            }
        } else {
            cout << "Não foi possível encontrar o voo selecionado." << endl;
        }
    }

    static void explodir_voo(int cod_voo){
        if (tem_voo(cod_voo) == true)
        {
            Voo* voo = Voo::recuperar_voo_cod(cod_voo);

            if (voo != nullptr && voo->estado_voo == EM_CURSO)
            {   
                voo->estado_voo = FINALIZADO_EX;

                for (string ast_v: voo->astronautas_cpf)
                {
                    Astronautas* ast = Astronautas::recuperar_astronauta_cpf(ast_v);
                    ast->esta_disponivel = false;
                    ast->esta_vivo = false;
                }
            } else {
                cout << "Por causas adversas, não foi possível realizar esta ação. ";
                cout << "Verifique o estado do voo." << endl;
            }
        } else {
            cout << "Não foi possível encontrar o voo selecionado." << endl;
        }
    }

    static void finalizar_voo(int cod_voo){
        if (tem_voo(cod_voo) == true)
        {
            Voo* voo = Voo::recuperar_voo_cod(cod_voo);

            if (voo != nullptr && voo->estado_voo == EM_CURSO)
            {   
                voo->estado_voo = FINALIZADO_S;

                for (string ast_v: voo->astronautas_cpf)
                {
                    Astronautas* ast = Astronautas::recuperar_astronauta_cpf(ast_v);
                    ast->esta_disponivel = true;
                }
            } else {
                cout << "Por causas adversas, não foi possível realizar esta ação. ";
                cout << "Verifique o estado do voo." << endl;
            }
        } else {
            cout << "Não foi possível encontrar o voo selecionado." << endl;
        }
    }

    static string listar_astro_mortos(){
        if (V_ASTRONAUTAS.empty() || V_VOOS.empty())
        {
            return "Não existe Astronautas ou Voos cadastrados.\n";
        }
        string mss;
        for (Astronautas ast: V_ASTRONAUTAS)
        {
            mss += "\n=============!+!=============\n";
            if(ast.esta_vivo == false){
                mss += "Cpf: " + ast.cpf + "\nNome: " + ast.nome + "\nVoos:";
                for (Voo &voo: V_VOOS){
                    if ((voo.estado_voo == FINALIZADO_EX || voo.estado_voo == FINALIZADO_S)
                        && voo.tem_astro_voo(ast.cpf))
                    {
                        mss += to_string(voo.codigo_voo) + " ";
                    }
                }
                mss += "\n";
            }
        }
        return mss;
    }
    static string listar_detalhes_voo(est_voo est){
        string mss;
        for (Voo &voo: V_VOOS)
        {
            if (voo.estado_voo == est)
            {
                mss += "Código do voo: " + voo.codigo_voo;
                mss += "\nEstado:" + voo.estado_voo;
                mss += "\nAstronautas no voo:\n";

                for (string ast_v: voo.astronautas_cpf)
                {
                    Astronautas* ast = Astronautas::recuperar_astronauta_cpf(ast_v);
                    mss += "CPF: "+ ast->cpf + "\tNome: " + ast->nome;
                }                
            }
        }

        return mss;
    }

    static string listar_voos(){
        if (V_VOOS.empty())
        {
            return "Não existe Voos cadastrados.\n";
        }
        string mss = "=============!+!=============\n";
        mss += "\n----PLANEJADOS----\n";
        mss += Voo::listar_detalhes_voo(PLANEJADO);
        mss += "\n----EM CURSO----\n";
        mss += Voo::listar_detalhes_voo(EM_CURSO);
        mss += "\n----FINALIZADOS COM SUCESSO----\n";
        mss += Voo::listar_detalhes_voo(FINALIZADO_S);
        mss += "\n----FINALIZADOS COM EXPLOSÃO----\n";
        mss += Voo::listar_detalhes_voo(FINALIZADO_EX);
        mss += "\n=============!+!=============";

        return mss;
    }

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
            
            if (operacao == "CADASTRAR_VOO") {
                int cod_voo;
                iss >> cod_voo;
                Voo::cadastrar_voo(cod_voo);
            }

            if (operacao == "ADICIONAR_ASTRONAUTA"){
                string cpf;
                int cod_voo;
                iss >> cpf >> cod_voo;
                Voo::adicionar_astronauta_voo(cpf, cod_voo);
            }

            if (operacao == "REMOVER_ASTRONAUTA") {
                string cpf;
                int cod;
                iss >> cpf >> cod;
                Voo::remover_astronauta_voo(cpf, cod);
            }

            if (operacao == "LANCAR_VOO") {
                int cod_voo;
                iss >> cod_voo;
                Voo::lancar_voo(cod_voo);
            }

            if (operacao == "EXPLODIR_VOO") {
                int cod_voo;
                iss >> cod_voo;
                Voo::explodir_voo(cod_voo);
            }

            if (operacao == "FINALIZAR_VOO") {
                int cod_voo;
                iss >> cod_voo;
                Voo::finalizar_voo(cod_voo);
            }

            if (operacao == "LISTAR_MORTOS")
            {
                cout << Voo::listar_astro_mortos() << endl;
            }

            if (operacao == "LISTAR_VOOS")
            {
                cout << Voo::listar_voos() << endl;
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

bool tem_voo(int cod){
    if (V_VOOS.empty())
    {
        return false;
    }
    
    for (Voo voo: V_VOOS)
    {
        if (voo.codigo_voo == cod)
        {
            return true;
        }
    }

    return false;
};
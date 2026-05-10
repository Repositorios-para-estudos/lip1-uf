#include "sistema.h"
#include <iostream>
#include <algorithm>

using namespace std;

bool Sistema::tem_cpf(string c) {
    for (auto &a : astronautas)
        if (a.cpf == c) return true;
    return false;
}

bool Sistema::tem_voo(int cod) {
    for (auto &v : voos)
        if (v.codigo_voo == cod) return true;
    return false;
}

Astronautas* Sistema::buscarAstronauta(string cpf) {
    for (auto &a : astronautas)
        if (a.cpf == cpf) return &a;
    cout << "Não foi encontrado nenhum astronauta com esse código." << endl;
    return nullptr;
}

Voo* Sistema::buscarVoo(int cod) {
    for (auto &v : voos)
        if (v.codigo_voo == cod) return &v;
    cout << "Não foi encontrado nenhum voo com esse código." << endl;
    return nullptr;
}

void Sistema::cadastrar_astronauta(string c, int i, string n) {
    if (!tem_cpf(c))
        astronautas.push_back(Astronautas(c, i, n));
    else
        cout << "O CPF " << c <<" já está cadastrado. Abortando admissão." << endl;
}

void Sistema::cadastrar_voo(int cod) {
    if (!tem_voo(cod))
        voos.push_back(Voo(cod));
    else
        cout << "O código de voo " << cod <<" já está cadastrado. Abortando admissão." << endl;
}

void Sistema::adicionar_astronauta_voo(string cpf, int cod_voo) {
    if (tem_cpf(cpf) && tem_voo(cod_voo)) {
        Astronautas* ast = buscarAstronauta(cpf);
        Voo* voo = buscarVoo(cod_voo);

        if (voo && voo->estado_voo == PLANEJADO && ast->esta_vivo && !voo->tem_astro_voo(cpf))
            voo->astronautas_cpf.push_back(cpf);
        else {
            cout << "Por causas adversas, não foi possível realizar esta ação. ";
            cout << "Verifique o estado do voo, astronautas ou a lista de passageiros." << endl;
        }
    } else {
        cout << "Não foi possível encontrar o astronauta/voo selecionado." << endl;
    }
}

void Sistema::remover_astronauta_voo(string cpf, int cod_voo) {
    if (tem_cpf(cpf) && tem_voo(cod_voo)) {
        Voo* voo = buscarVoo(cod_voo);

        if (voo && voo->estado_voo == PLANEJADO && voo->tem_astro_voo(cpf)) {
            voo->astronautas_cpf.erase(
                remove(voo->astronautas_cpf.begin(), voo->astronautas_cpf.end(), cpf),
                voo->astronautas_cpf.end());
        } else {
            cout << "Por causas adversas, não foi possível realizar esta ação. ";
            cout << "Verifique o estado do voo ou a lista de passageiros." << endl;
        }
    } else {
        cout << "Não foi possível encontrar o astronauta/voo selecionado." << endl;
    }
}


void Sistema::lancar_voo(int cod_voo) {
    if (tem_voo(cod_voo)) {
        Voo* voo = buscarVoo(cod_voo);

        if (voo && voo->estado_voo == PLANEJADO && !voo->astronautas_cpf.empty()) {
            bool todos_disp = true;

            for (string ast_v : voo->astronautas_cpf) {
                Astronautas* ast = buscarAstronauta(ast_v);
                if (!ast->esta_disponivel || !ast->esta_vivo) {
                    todos_disp = false;
                    cout << "O astronauta de cpf:" << ast_v << " não poderá participar do lançamento." << endl;
                    cout << "Abortando missão..." << endl;
                    break;
                }
            }

            if (todos_disp) {
                voo->estado_voo = EM_CURSO;
                for (string ast_v : voo->astronautas_cpf)
                    buscarAstronauta(ast_v)->esta_disponivel = false;
            }
        } else {
            cout << "Por causas adversas, não foi possível realizar esta ação.";
            cout << "verifique o estado do voo ou se há algum passageiro." << endl;
        }
    } else {
        cout << "Não foi possível encontrar o voo selecionado." << endl;
    }
}

void Sistema::explodir_voo(int cod_voo) {
    if (tem_voo(cod_voo)) {
        Voo* voo = buscarVoo(cod_voo);

        if (voo && voo->estado_voo == EM_CURSO) {
            voo->estado_voo = FINALIZADO_EX;

            for (string ast_v : voo->astronautas_cpf) {
                Astronautas* ast = buscarAstronauta(ast_v);
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

void Sistema::finalizar_voo(int cod_voo) {
    if (tem_voo(cod_voo)) {
        Voo* voo = buscarVoo(cod_voo);

        if (voo && voo->estado_voo == EM_CURSO) {
            voo->estado_voo = FINALIZADO_S;

            for (string ast_v : voo->astronautas_cpf)
                buscarAstronauta(ast_v)->esta_disponivel = true;
        } else {
            cout << "Por causas adversas, não foi possível realizar esta ação. ";
            cout << "Verifique o estado do voo." << endl;
        }
    } else {
        cout << "Não foi possível encontrar o voo selecionado." << endl;
    }
}

string Sistema::listar_astro_mortos() {
    if (astronautas.empty() || voos.empty())
        return "Não existe Astronautas ou Voos cadastrados.\n";

    string mss;

    for (auto &ast : astronautas) {
        mss += "\n=============!+!=============\n";
        if (!ast.esta_vivo) {
            mss += "Cpf: " + ast.cpf + "\nNome: " + ast.nome + "\nVoos:";

            for (auto &voo : voos) {
                if ((voo.estado_voo == FINALIZADO_EX || voo.estado_voo == FINALIZADO_S)
                    && voo.tem_astro_voo(ast.cpf))
                    mss += to_string(voo.codigo_voo) + " ";
            }
            mss += "\n";
        }
    }

    return mss;
}

string Sistema::listar_detalhes_voo(est_voo est) {
    string mss;

    for (auto &voo : voos) {
        if (voo.estado_voo == est) {
            mss += "Código do voo: " + to_string(voo.codigo_voo);
            mss += "\nEstado:" + to_string(voo.estado_voo);
            mss += "\nAstronautas no voo:\n";

            for (string ast_v : voo.astronautas_cpf) {
                Astronautas* ast = buscarAstronauta(ast_v);
                mss += "CPF: "+ ast->cpf + "\tNome: " + ast->nome;
            }
        }
    }

    return mss;
}

string Sistema::listar_voos() {
    if (voos.empty())
        return "Não existe Voos cadastrados.\n";

    string mss = "=============!+!=============\n";
    mss += "\n----PLANEJADOS----\n";
    mss += listar_detalhes_voo(PLANEJADO);
    mss += "\n----EM CURSO----\n";
    mss += listar_detalhes_voo(EM_CURSO);
    mss += "\n----FINALIZADOS COM SUCESSO----\n";
    mss += listar_detalhes_voo(FINALIZADO_S);
    mss += "\n----FINALIZADOS COM EXPLOSÃO----\n";
    mss += listar_detalhes_voo(FINALIZADO_EX);
    mss += "\n=============!+!=============";

    return mss;
}
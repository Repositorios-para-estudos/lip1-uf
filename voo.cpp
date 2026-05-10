#include "voo.h"

Voo::Voo(int cod) : codigo_voo(cod) {}

bool Voo::tem_astro_voo(string cpf) {
    for (string c : astronautas_cpf) {
        if (c == cpf) return true;
    }
    return false;
}
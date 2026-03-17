#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Use: %s <C/F> <valor>\n", argv[0]);
        return 1;
    }

    char tipo = argv[1][0];
    float valor = atof(argv[2]);
    float resultado;

    if (tipo == 'C' || tipo == 'c') {
        resultado = (valor * 9.0 / 5.0) + 32.0;
    } else if (tipo == 'F' || tipo == 'f') {
        resultado = (valor - 32.0) * 5.0 / 9.0;
    } else {
        fprintf(stderr, "Erro: Tipo inválido. Use 'C' para Celsius ou 'F' para Fahrenheit.\n");
        return 1;
    }
    printf("%.1f °%c é igual a %.1f °C\n", valor, tipo, resultado);

    return 0;
}

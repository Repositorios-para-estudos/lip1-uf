#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool isPrimo(int numero);

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Use: %s <número para verificar se é primo>\n", argv[0]);
        return 1;
    }

    int numero = atoi(argv[1]);

    if (isPrimo(numero)) {
        printf("%d é um número primo.\n", numero);
    } else {
        printf("%d não é um número primo.\n", numero);
    }

    return 0;
}

bool isPrimo(int numero) {
    if (numero <= 1) {
        return false;
    }
    for (int i = 2; i <= numero / 2; i++) {
        if (numero % i == 0) {
            return false;
        }
    }
    return true;
}
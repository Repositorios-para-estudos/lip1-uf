#include <stdio.h>
#include <stdlib.h>

int fatorial(int n);

int main(int argc, char *argv[]){
    if (argc < 2) {
        printf("Usage: %s <número pro fatorial>\n", argv[0]);
        return 1;
    }

    int numero = atoi(argv[1]);
    int resultado = fatorial(numero);

    printf("O fatorial de %d é: %d\n", numero, resultado);

    return 0;
}

int fatorial(int n){
    if (n == 0) {
        return 1;
    }
    return n * fatorial(n - 1);
}
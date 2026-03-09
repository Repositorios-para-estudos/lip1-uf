#include <stdio.h>
#include <stdlib.h>

#define TAMANHO_ARRAY   5

int somaArray(int *array, int tamanho);

int main(int argc, char *argv[]){
    if (argc < 2) {
        fprintf(stderr, "Use: %s <5 elementos para compor o array>\n", argv[0]);
        return 1;
    }

    if (argc != TAMANHO_ARRAY + 1) {
        fprintf(stderr, "Erro: Você deve fornecer exatamente %d elementos para o array.\n", TAMANHO_ARRAY);
        return 1;
    }

    int array[TAMANHO_ARRAY];
    for (int i = 0; i < TAMANHO_ARRAY; i++) {
        array[i] = atoi(argv[i + 1]);
    }

    int resultado = somaArray(array, TAMANHO_ARRAY);

    printf("A soma dos elementos do array é: %d\n", resultado);

    return 0;
}

int somaArray(int *array, int tamanho) {
    int soma = 0;
    for (int i = 0; i < tamanho; i++) {
        soma += array[i];
    }
    return soma;
}

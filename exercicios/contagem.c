#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
    if (argc != 2) {
        fprintf(stderr, "Uso: %s \"string de entrada\"\n", argv[0]);
        exit(1);
    }

    char *entrada = argv[1];
    int tamanho = strlen(entrada);

    printf("Tamanho da string é: %d\n", tamanho);

    return 0;
}
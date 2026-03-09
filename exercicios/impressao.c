#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    if (argc < 2) {
        printf("Usage: %s <número pra imprimir>\n", argv[0]);
        return 1;
    }

    int numero = atoi(argv[1]);

    for (int i = 1; i <= numero; i++)
    {
        printf("-> %d\t", i);
    }
    
    return 0;
}
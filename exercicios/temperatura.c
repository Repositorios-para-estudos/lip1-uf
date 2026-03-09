#include <stdio.h>
#include <stdlib.h>

float celsiusToFahrenheit(float celsius);
float fahrenheitToCelsius(float fahrenheit);

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Use: %s <C|F> <valor>\n", argv[0]);
        return 1;
    }

    char tipo = argv[1][0];
    float valor = atof(argv[2]);
    float resultado;

    if (tipo == 'C' || tipo == 'c') {
        resultado = celsiusToFahrenheit(valor);
        printf("%.1f °C é igual a %.1f °F\n", valor, resultado);
    } else if (tipo == 'F' || tipo == 'f') {
        resultado = fahrenheitToCelsius(valor);
        printf("%.1f °F é igual a %.1f °C\n", valor, resultado);
    } else {
        fprintf(stderr, "Erro: Tipo inválido. Use 'C' para Celsius ou 'F' para Fahrenheit.\n");
        return 1;
    }

    return 0;
}

float celsiusToFahrenheit(float celsius) {
    return (celsius * 9.0 / 5.0) + 32.0;
}

float fahrenheitToCelsius(float fahrenheit) {
    return (fahrenheit - 32.0) * 5.0 / 9.0;
}
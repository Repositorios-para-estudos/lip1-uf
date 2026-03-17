
# Aula 0 (Linguagem de Programação I)

Este repositório consiste na lista de avaliação 0 da matéria de **Linguagem de Programação I**.

## Compilação e Execução

Cada exercício proposto possui um arquivo de resolução, execute os seguintes comandos no terminal para ver a resolução de cada.

### Impressão de Números de 1 a N
```bash
gcc ./exercicios/impressao.c -o ./execR/imp
./execR/imp 40
```

### Cálculo de Fatorial
```bash
./exercicios/fatorial.c -o ./execR/fat
./execR/fat 5
```

### Soma de Números em um Array
```bash
gcc ./exercicios/somaArray.c -o ./execR/somA
./execR/somA 7 5 89 2 3
```

### Conversão de Temperatura
```bash
gcc ./exercicios/temperatura.c -o ./execR/tmp
# 'c' para converter uma temperatuda de celsius -> fahrenheit
./execR/tmp c 30

# 'f' para converter uma temperatuda de fahrenheit -> celsius
./execR/tmp f 86
```

### Contagem de Caracteres em uma String
```bash
./exercicios/contagem.c -o ./execR/cont
./execR/cont "olá mundo!"
```

### Verificação de Número Primo
```bash
gcc ./exercicios/primo.c -o ./execR/primo
./execR/primo 3117
```
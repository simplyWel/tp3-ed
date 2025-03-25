// tp.c deve apenas invocar, tratar as respostas das funções e procedimentos definidos no arquivo indiceInvertido.h e impressões necessárias

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "indiceInvertido.h"
#include "hash.h"

int main() {
    HashTable *indice = aloca(100); // Inicializa o índice invertido com tamanho 100

    int n;
    scanf("%d", &n); // Lê o número de documentos
    for (int i = 0; i < n; i++) {
        char nomeArquivo[100];
        char palavra[20];

        // Lê o nome do arquivo
        scanf("%s", nomeArquivo);

        // Lê as palavras associadas ao arquivo até o final da linha
        while (scanf("%s", palavra) == 1) {
            if (strcmp(palavra, "I") == 0) {
                break; // Sai do loop se encontrar o comando "I"
            }
            inserePalavra(palavra, nomeArquivo); // Insere a palavra e o documento no índice
        }
    }

    imprime(indice); // Imprime o índice invertido para verificação

    libera(indice); // Libera os recursos alocados
    return 0;
}
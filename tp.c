
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "indiceInvertido.h"
#include "hash.h"

int main() {
    HashTable *indice = aloca(100); // Inicializa o índice invertido com tamanho 100
    int n;

    // Lê o número de documentos
    scanf("%d", &n);
    getchar(); // Consome o caractere de nova linha após o número

    for (int i = 0; i < n; i++) {
        char linha[200]; // Buffer para armazenar a linha inteira
        char nomeArquivo[100];

        // Lê o nome do arquivo
        scanf("%s", nomeArquivo);
        getchar(); // Consome o caractere de nova linha após o nome do arquivo

        // Lê a linha com as palavras associadas ao arquivo
        if (fgets(linha, sizeof(linha), stdin) != NULL) {
            // Remove o caractere de nova linha, se existir
            linha[strcspn(linha, "\n")] = '\0';

            // Divide a linha em palavras usando strtok
            char *palavra = strtok(linha, " ");
            while (palavra != NULL) {
                inserePalavra(palavra, nomeArquivo); // Insere a palavra e o documento no índice
                palavra = strtok(NULL, " "); // Próxima palavra
            }
        }
    }
    char opcao;
    scanf("%c", &opcao);
    if (opcao == 'I' || opcao == 'i'){
        ordenaPalavras(indice);
        for (int i = 0; i < indice->tamanho; i++) {
            if (indice->tabela[i].qtdDocumentos > 0) {
                ordenaDocumentos(&indice->tabela[i]);
            }
        }
        // Imprime o índice invertido
        imprime(indice);
    } else if (opcao == 'B' || opcao == 'B'){
        char linha[200];
        getchar(); // Consome o caractere de nova linha após o comando
        if (fgets(linha, sizeof(linha), stdin) != NULL) {
            linha[strcspn(linha, "\n")] = '\0'; // Remove o caractere de nova linha
            char *palavras[20];
            int qtdPalavras = 0;

            // Divide a linha em palavras usando strtok
            char *palavra = strtok(linha, " ");
            while (palavra != NULL) {
                palavras[qtdPalavras++] = palavra;
                palavra = strtok(NULL, " ");
            }

            // Chama a função consulta para buscar os documentos
            consulta(indice, palavras, qtdPalavras);
        }
    }
    // Libera os recursos alocados
    libera(indice);
    return 0;
}
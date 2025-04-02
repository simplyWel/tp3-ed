#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#include <ctype.h>
#include "indiceInvertido.h"
#include "hash.h"

int main() {
    HashTable *indice = aloca(MAX_TAMANHO_VOCABULARIO);
    if(indice == NULL) { 
        printf("\nERRO: tabela hash não alocada\n");
        return 1;
    }

    int n;
    scanf("%d", &n);
    getchar();
    
    if (n > MAX_DOCUMENTOS) {
        printf("\nERRO: Número de documentos (%d) excede o limite máximo permitido (%d).\n", n, MAX_DOCUMENTOS); 
        return 1;
    }

    for (int i = 0; i < n; i++) {
        char linha[MAX_TAMANHO_LINHA];
        char nomeArquivo[MAX_TAMANHO_DOCUMENTO + 1];

        scanf("%s", nomeArquivo);
        getchar();

        if (strlen(nomeArquivo) > MAX_TAMANHO_DOCUMENTO) { 
            printf("\nERRO: Nome do documento '%s' excede o limite máximo de %d caracteres.\n", nomeArquivo, MAX_TAMANHO_DOCUMENTO);
            continue;
        }

        if (fgets(linha, sizeof(linha), stdin) != NULL) {
            linha[strcspn(linha, "\n")] = '\0';

            char *palavra = strtok(linha, " "); //strtok divide a string em palavras
            int contPalavras = 0;
            
            while (palavra != NULL) {
                if (contPalavras > MAX_PALAVRAS_POR_DOCUMENTO) {
                    printf("\nERRO: Número de palavras no documento '%s' excede o limite máximo de %d.\n", nomeArquivo, MAX_PALAVRAS_POR_DOCUMENTO);
                    break;
                }
                if (strlen(palavra) > MAX_TAMANHO_PALAVRA) {
                    printf("\nErro: Palavra '%s' excede o limite máximo de %d caracteres.\n", palavra, MAX_TAMANHO_PALAVRA);
                    palavra = strtok(NULL, " ");
                    continue;
                }
                
                insereDocumento(indice, palavra, nomeArquivo);
                palavra = strtok(NULL, " "); 
                contPalavras++;
            }
        }
    }

    char opcao;
    scanf("%c", &opcao);
    getchar();
    
    if (toupper(opcao) == 'I') {
        imprime(indice);
    } else if (toupper(opcao) == 'B') {
        lePalavra(indice);
    } else {
        printf("\nERRO: Opção inválida '%c'.\n", opcao);
    }

    libera(indice);
    return 0;
}
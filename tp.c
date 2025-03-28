#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "indiceInvertido.h"
#include "hash.h"

int main() {

    HashTable *indice = aloca(MAX_TAMANHO_VOCABULARIO); // Inicializa o índice invertido com tamanho 1000
    if(indice == NULL){ 
        printf("\nERRO: tabela hash não alocada\n");
        return 1;
    } // Verifica se a alocação foi mal-sucedida
    int n;

    scanf("%d", &n); // Lê o número de documentos
    getchar(); // Consome o caractere de nova linha após o número
    if (n > MAX_DOCUMENTOS){
        printf("\nERRO: Número de documentos (%d) excede o limite máximo permitido (%d).\n", n, MAX_DOCUMENTOS); 
        return 1;
    }

    for (int i = 0; i < n; i++) {
        char linha[MAX_TAMANHO_LINHA]; // Buffer para armazenar a linha inteira
        char nomeArquivo[MAX_TAMANHO_DOCUMENTO + 1];

        // Lê o nome do arquivo
        scanf("%s", nomeArquivo);
        getchar(); // Consome o caractere de nova linha após o nome do arquivo

        if (strlen(nomeArquivo) > MAX_TAMANHO_DOCUMENTO){ 
            printf("\nERRO: Nome do documento '%s' excede o limite máximo de %d caracteres.\n", nomeArquivo, MAX_TAMANHO_DOCUMENTO);
            continue;
        }

        // Lê a linha com as palavras associadas ao arquivo
        if (fgets(linha, sizeof(linha), stdin) != NULL) {
            // Remove o caractere de nova linha, se existir
            linha[strcspn(linha, "\n")] = '\0';

            // Divide a linha em palavras usando strtok
            char *palavra = strtok(linha, " ");
            int contPalavras = 0;
            while (palavra != NULL) {
                if (contPalavras > MAX_PALAVRAS_POR_DOCUMENTO) {
                    printf("\nERRO: Número de palavras no documento '%s' excede o limite máximo de %d.\n", nomeArquivo, MAX_PALAVRAS_POR_DOCUMENTO);
                    break;
                }
                if (strlen(palavra) > MAX_TAMANHO_PALAVRA) {
                    printf("\nErro: Palavra '%s' excede o limite máximo de %d caracteres.\n", palavra, MAX_TAMANHO_PALAVRA);
                    palavra = strtok(NULL, " "); // Próxima palavra
                    continue;
                }
                inserePalavra(palavra, nomeArquivo); // Insere a palavra e o documento no índice
                palavra = strtok(NULL, " "); // Próxima palavra
                contPalavras++;
            }
        }
    }
    char opcao;
    scanf("%c", &opcao);
    if (opcao == 'I' || opcao == 'i') { 
        // Imprime o índice invertido
        imprime(indice);
    } else if (opcao == 'B' || opcao == 'b') {
        char linha[MAX_TAMANHO_LINHA];
        getchar(); // Consome o caractere de nova linha após o comando
        if (fgets(linha, sizeof(linha), stdin) != NULL) {
            linha[strcspn(linha, "\n")] = '\0'; // Remove o caractere de nova linha
            char *palavras[MAX_PALAVRAS_BUSCADAS];
            int qtdPalavras = 0;
    
            // Divide a linha em palavras usando strtok
            char *palavra = strtok(linha, " ");
            while (palavra != NULL) {
                if (qtdPalavras > MAX_PALAVRAS_BUSCADAS) {
                    printf("\nERRO: Número de palavras buscadas excede o limite máximo de %d.\n", MAX_PALAVRAS_BUSCADAS);
                    break;
                }
                palavras[qtdPalavras++] = palavra;
                palavra = strtok(NULL, " ");
            }
            for (int i = 0; i < indice->tamanho; i++) {
                if (indice->tabela[i].qtdDocumentos > 0) {
                    ordenaDocumentos(&indice->tabela[i]);
                }
            }
            // Chama a função consulta para buscar os documentos
            consulta(indice, palavras, qtdPalavras);
        }
    } 
    // imprimeHash(indice); // Para depuração, imprime o índice hash
    libera(indice);
    return 0;
}
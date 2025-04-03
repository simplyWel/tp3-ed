#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "indiceInvertido.h"
#include "hash.h"

HashTable* aloca(int tamanho) {
    HashTable *hash = (HashTable *)malloc(sizeof(HashTable));
    hash->tabela = (EntradaHash *)calloc(tamanho, sizeof(EntradaHash));
    hash->tamanho = tamanho;
    return hash;;
}

void libera(HashTable *hash) {
    free(hash->tabela);
    free(hash);
}

void insereDocumento(HashTable *indice, char *palavra, char *documento) {
    int idx = hashFunction(palavra, indice->tamanho);
    for (int i = 0; i < indice->tamanho; i++) {
        int pos = (idx + i) % indice->tamanho;

        if (indice->tabela[pos].qtdDocumentos == 0) {
            strcpy(indice->tabela[pos].palavra, palavra);
            strcpy(indice->tabela[pos].documentos[0], documento);
            indice->tabela[pos].qtdDocumentos = 1;
            return;
        }

        if (strcmp(indice->tabela[pos].palavra, palavra) == 0) {
            for (int j = 0; j < indice->tabela[pos].qtdDocumentos; j++) {
                if (strcmp(indice->tabela[pos].documentos[j], documento) == 0) {
                    return;
                }
            }
            strcpy(indice->tabela[pos].documentos[indice->tabela[pos].qtdDocumentos], documento);
            indice->tabela[pos].qtdDocumentos++;
            return;
        }
    }
}

int busca(HashTable *hash, char *palavra, EntradaHash **resultado) {
    int idx = hashFunction(palavra, hash->tamanho);
    
    for (int i = 0; i < hash->tamanho; i++) {
        int pos = (idx + i) % hash->tamanho;
        if (hash->tabela[pos].qtdDocumentos == 0) {
            return 0;
        }
        if (strcmp(hash->tabela[pos].palavra, palavra) == 0) {
            *resultado = &hash->tabela[pos];
            return 1;
        }
    }
    
    return 0;
}

void consulta(HashTable *indice, char **palavras, int qtdPalavras) {
    if (qtdPalavras > MAX_PALAVRAS_BUSCADAS) {
        printf("ERRO: Número de palavras buscadas excede o limite máximo.\n");
        return;
    }

    int encontrados[MAX_DOCUMENTOS] = {0}; // Array para marcar documentos válidos
    char *documentos[MAX_DOCUMENTOS];      // Array para armazenar os nomes dos documentos
    int totalDocumentos = 0;

    // Itera sobre todas as palavras fornecidas
    for (int i = 0; i < qtdPalavras; i++) {
        EntradaHash *resultado; 
        if (busca(indice, palavras[i], &resultado)) {
            // Para a primeira palavra, inicializa o array de documentos
            if (i == 0) {
                for (int j = 0; j < resultado->qtdDocumentos; j++) {
                    documentos[j] = resultado->documentos[j];
                    encontrados[j] = 1; // Marca o documento como válido
                }
                totalDocumentos = resultado->qtdDocumentos;
            } else {
                // Para as palavras subsequentes, verifica quais documentos ainda são válidos
                for (int j = 0; j < totalDocumentos; j++) {
                    if (encontrados[j]) { // Verifica apenas os documentos marcados como válidos
                        int encontrado = 0;
                        for (int k = 0; k < resultado->qtdDocumentos; k++) {
                            if (strcmp(documentos[j], resultado->documentos[k]) == 0) {
                                encontrado = 1;
                                break;
                            }
                        }
                        if (!encontrado) {
                            encontrados[j] = 0; // Marca o documento como inválido
                        }
                    }
                }
            }
        } else {
            // Se uma palavra não for encontrada, nenhum documento contém todas as palavras
            printf("none\n");
            return;
        }
    }

    // Ordena os documentos encontrados
    int count = 0;
    char *documentosValidos[MAX_DOCUMENTOS];
    for (int i = 0; i < totalDocumentos; i++) {
        if (encontrados[i]) {
            documentosValidos[count++] = documentos[i];
        }
    }

    if (count == 0) {
        printf("none\n");
        return;
    }

    quickSort(documentosValidos, 0, count - 1);

    // Imprime os documentos que contêm todas as palavras
    for (int i = 0; i < count; i++) {
        printf("%s\n", documentosValidos[i]);
    }
}

void imprime(HashTable *indice) {
    for (int i = 0; i < indice->tamanho; i++) {
        if (indice->tabela[i].qtdDocumentos > 0) {
            printf("%s - ", indice->tabela[i].palavra);
            for (int j = 0; j < indice->tabela[i].qtdDocumentos; j++) {
                printf("%s ", indice->tabela[i].documentos[j]);
            }
            printf("\n");
        }
    }
}

void lePalavra(HashTable *indice){
    char linha[MAX_TAMANHO_LINHA];
    if (fgets(linha, sizeof(linha), stdin) != NULL) {
        linha[strcspn(linha, "\n")] = '\0';
        char *palavras[MAX_PALAVRAS_BUSCADAS];
        int qtdPalavras = 0;

        char *palavra = strtok(linha, " ");
        while (palavra != NULL) {
            palavras[qtdPalavras++] = palavra;
            palavra = strtok(NULL, " ");
        }
        if (qtdPalavras > MAX_PALAVRAS_BUSCADAS) {
            printf("ERRO: quantidade de palavras buscadas(%d) exedem o limite máximo(%d)\n", qtdPalavras, MAX_PALAVRAS_BUSCADAS);
            return;
        } else 
            consulta(indice, palavras, qtdPalavras);
    }
}


void quickSort(char **documentos, int inicio, int fim) {
    if (inicio < fim) {
        int pivo = particiona(documentos, inicio, fim);
        quickSort(documentos, inicio, pivo - 1);
        quickSort(documentos, pivo + 1, fim);
    }
}

int particiona(char **documentos, int inicio, int fim) {
    char pivo[MAX_TAMANHO_DOCUMENTO + 1];
    strcpy(pivo, documentos[fim]);
    int i = inicio - 1;

    for (int j = inicio; j < fim; j++) {
        if (strcmp(documentos[j], pivo) <= 0) {
            i++;
            char *temp = documentos[i];
            documentos[i] = documentos[j];
            documentos[j] = temp;
        }
    }

    char *temp = documentos[i + 1];
    documentos[i + 1] = documentos[fim];
    documentos[fim] = temp;

    return i + 1;
}
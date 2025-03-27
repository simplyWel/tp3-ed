#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "indiceInvertido.h"
#include "hash.h"

static HashTable *indice;

int comparaEntradas(const void *a, const void *b) {
    EntradaHash *entradaA = (EntradaHash *)a;
    EntradaHash *entradaB = (EntradaHash *)b;
    return strcmp(entradaA->palavra, entradaB->palavra);
}

void ordenaPalavras(HashTable *indice) {
    qsort(indice->tabela, indice->tamanho, sizeof(EntradaHash), comparaEntradas);
}

void ordenaDocumentos(EntradaHash *entrada) {
    qsort(entrada->documentos, entrada->qtdDocumentos, sizeof(entrada->documentos[0]), (int (*)(const void *, const void *))strcmp);
}



HashTable* aloca(int tamanho) {
    if (tamanho > MAX_VOCABULARIO)  return NULL;
    indice = criaHash(tamanho); // Inicializa a tabela hash com o tamanho especificado
    return indice; // Retorna o ponteiro para a tabela hash
}

void libera(HashTable *indice) {
    liberaHash(indice); // Libera a memória da tabela hash
}

void insereDocumento(char *palavra, char *documento) {
    insereHash(indice, palavra, documento); // Usa a função da tabela hash para inserir
}

int busca(char *palavra) {
    EntradaHash *resultado;
    if (buscaHash(indice, palavra, &resultado)) {
        return 1; // Palavra encontrada
    }
    return 0; // Palavra não encontrada
}

void consulta(HashTable *indice, char **palavras, int qtdPalavras) {
    if (qtdPalavras > MAX_PALAVRAS_BUSCADAS) return;

    int encontrados[MAX_DOCUMENTOS] = {0}; // Array para contar os documentos encontrados
    char *documentos[MAX_DOCUMENTOS];      // Array para armazenar os nomes dos documentos
    int totalDocumentos = 0;

    // Itera sobre todas as palavras fornecidas
    for (int i = 0; i < qtdPalavras; i++) {
        EntradaHash *resultado;
        if (buscaHash(indice, palavras[i], &resultado)) {
            // Para a primeira palavra, inicializa o array de documentos
            if (i == 0) {
                for (int j = 0; j < resultado->qtdDocumentos; j++) {
                    documentos[j] = resultado->documentos[j];
                    encontrados[j] = 1; // Marca o documento como encontrado para a primeira palavra
                }
                totalDocumentos = resultado->qtdDocumentos;
            } else {
                // Para as palavras subsequentes, verifica quais documentos ainda são válidos
                for (int j = 0; j < totalDocumentos; j++) {
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
        } else {
            // Se uma palavra não for encontrada, nenhum documento contém todas as palavras
            printf("none\n");
            return;
        }
    }

    // Imprime os documentos que contêm todas as palavras
    int encontrouAlgum = 0;
    for (int i = 0; i < totalDocumentos; i++) {
        if (encontrados[i]) {
            printf("%s\n", documentos[i]);
            encontrouAlgum = 1;
        }
    }

    if (!encontrouAlgum) {
        printf("none\n");
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

void inserePalavra(char *palavra, char *documento) {
    EntradaHash *resultado;
    if (buscaHash(indice, palavra, &resultado)) {
        if (resultado->qtdDocumentos > MAX_PALAVRAS_POR_DOCUMENTO) return;
        // Verifica se o documento já está associado à palavra
        for (int i = 0; i < resultado->qtdDocumentos; i++) {
            if (strcmp(resultado->documentos[i], documento) == 0) {
                return; // Documento já associado, não faz nada
            }
        }
        // Adiciona o documento à lista de documentos da palavra
        strcpy(resultado->documentos[resultado->qtdDocumentos], documento);
        resultado->qtdDocumentos++;
    } else {
        // Palavra não encontrada, insere uma nova entrada
        insereHash(indice, palavra, documento);
    }
}


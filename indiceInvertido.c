#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "indiceInvertido.h"
#include "hash.h"

static HashTable *indice;

HashTable* aloca(int tamanho) {
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

void consulta(char **palavras, int qtdPalavras) {
    int encontrados[100] = {0}; // Array para contar os documentos encontrados
    for (int i = 0; i < qtdPalavras; i++) {
        EntradaHash *resultado;
        if (buscaHash(indice, palavras[i], &resultado)) {
            for (int j = 0; j < resultado->qtdDocumentos; j++) {
                encontrados[j]++;
            }
        } else {
            printf("none\n");
            return; // Se uma palavra não for encontrada, não há documentos que contenham todas
        }
    }

    // Imprime os documentos que contêm todas as palavras
    for (int i = 0; i < 100; i++) {
        if (encontrados[i] == qtdPalavras) {
            printf("%s ", indice->tabela[i].documentos[i]);
        }
    }
    printf("\n");
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


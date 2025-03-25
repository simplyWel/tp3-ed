#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

static int hashFunction(char *palavra, int tamanho) {
    int hash = 0;
    for (int i = 0; palavra[i] != '\0'; i++) {
        hash = (hash * 31 + palavra[i]) % tamanho;
    }
    return hash;
}

HashTable* criaHash(int tamanho) {
    HashTable *hash = (HashTable *)malloc(sizeof(HashTable));
    hash->tabela = (EntradaHash *)calloc(tamanho, sizeof(EntradaHash));
    hash->tamanho = tamanho;
    return hash;
}

void liberaHash(HashTable *hash) {
    free(hash->tabela);
    free(hash);
}

int insereHash(HashTable *hash, char *palavra, char *documento) {
    int idx = hashFunction(palavra, hash->tamanho);
    for (int i = 0; i < hash->tamanho; i++) {
        int pos = (idx + i) % hash->tamanho;
        if (hash->tabela[pos].qtdDocumentos == 0 || strcmp(hash->tabela[pos].palavra, palavra) == 0) {
            if (hash->tabela[pos].qtdDocumentos == 0) {
                strcpy(hash->tabela[pos].palavra, palavra);
            }
            strcpy(hash->tabela[pos].documentos[hash->tabela[pos].qtdDocumentos++], documento);
            return 1;
        }
    }
    return 0; // Tabela cheia
}

int buscaHash(HashTable *hash, char *palavra, EntradaHash **resultado) {
    int idx = hashFunction(palavra, hash->tamanho);
    for (int i = 0; i < hash->tamanho; i++) {
        int pos = (idx + i) % hash->tamanho;
        if (hash->tabela[pos].qtdDocumentos == 0) {
            return 0; // Não encontrado
        }
        if (strcmp(hash->tabela[pos].palavra, palavra) == 0) {
            *resultado = &hash->tabela[pos];
            return 1;
        }
    }
    return 0; // Não encontrado
}
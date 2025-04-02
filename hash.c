#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"


int hashFunction(char *chave, int m) {
    float p[] = {0.8326030060567271, 0.3224428884580177, 
    0.6964223353369197, 0.1966079596929834, 
    0.8949283476433433, 0.4587297824155836, 
    0.5100785238948532, 0.05356055934904358, 
    0.9157270141062215, 0.7278472432221632};
    int tamP = 10;
    unsigned int soma = 0;
    for (int i = 0; i < strlen(chave); i++) {
        soma += (unsigned int)chave[i] * p[i % tamP];
    }
    return soma % m;
}


HashTable* criaHash(int tamanho) {
    if (tamanho > MAX_TAMANHO_VOCABULARIO) return NULL; // Verifica se o tamanho é válido
    HashTable *hash = (HashTable *)malloc(sizeof(HashTable));
    hash->tabela = (EntradaHash *)calloc(tamanho, sizeof(EntradaHash));
    hash->tamanho = tamanho;
    return hash;
}



int buscaHash(HashTable *hash, char *palavra, EntradaHash **resultado) {
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



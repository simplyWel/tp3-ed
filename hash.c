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
    
    void liberaHash(HashTable *hash) {
        free(hash->tabela);
        free(hash);
    }
    
    int insereHash(HashTable *hash, char *palavra, char *documento) {
        int idx = hashFunction(palavra, hash->tamanho);
        for (int i = 0; i < hash->tamanho; i++) {
            int pos = (idx + i) % hash->tamanho;
            
            if (hash->tabela[pos].qtdDocumentos == 0) {
                strcpy(hash->tabela[pos].palavra, palavra);
                strcpy(hash->tabela[pos].documentos[0], documento);
                hash->tabela[pos].qtdDocumentos = 1;
                return 1;
            }
            
            if (strcmp(hash->tabela[pos].palavra, palavra) == 0) {
                for (int j = 0; j < hash->tabela[pos].qtdDocumentos; j++) {
                if (strcmp(hash->tabela[pos].documentos[j], documento) == 0) {
                    return 1;
                }
            }
            strcpy(hash->tabela[pos].documentos[hash->tabela[pos].qtdDocumentos], documento);
            hash->tabela[pos].qtdDocumentos++;
            return 1;
        }
    }
    
    return 0;
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



// Função para depuração: imprime os índices ocupados na tabela hash
void imprimeHash(HashTable *hash) {
    printf("Índices ocupados na tabela hash:\n");
    for (int i = 0; i < hash->tamanho; i++) {
        if (hash->tabela[i].qtdDocumentos > 0) { // Verifica se o índice está ocupado
            printf("Índice %d: Palavra = '%s', Documentos = [", i, hash->tabela[i].palavra);
            for (int j = 0; j < hash->tabela[i].qtdDocumentos; j++) {
                printf("%s", hash->tabela[i].documentos[j]);
                if (j < hash->tabela[i].qtdDocumentos - 1) {
                    printf(", ");
                }
            }
            printf("]\n");
        }
    }
}

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
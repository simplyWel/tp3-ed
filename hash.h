#ifndef HASH_H
#define HASH_H

typedef struct {
    char palavra[20];
    char documentos[100][100];
    int qtdDocumentos;
} EntradaHash;

typedef struct {
    EntradaHash *tabela;
    int tamanho;
} HashTable;

HashTable* criaHash(int tamanho);
void liberaHash(HashTable *hash);
int insereHash(HashTable *hash, char *palavra, char *documento);
int buscaHash(HashTable *hash, char *palavra, EntradaHash **resultado);

#endif // HASH_H
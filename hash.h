#ifndef HASH_H
#define HASH_H

#define MAX_DOCUMENTOS 100
#define MAX_TAMANHO_PALAVRA 20
#define MAX_TAMANHO_DOCUMENTO 50
#define MAX_TAMANHO_VOCABULARIO 1000
#define MAX_PALAVRAS_BUSCADAS 100
#define MAX_PALAVRAS_POR_DOCUMENTO 1000


typedef struct {
    char palavra[20];
    char documentos[100][100];
    int qtdDocumentos;
} EntradaHash;

typedef struct {
    EntradaHash *tabela;
    int tamanho;
} HashTable;



HashTable* aloca(int tamanho);
int hashFunction(char *chave, int m);
HashTable* criaHash(int tamanho);
void liberaHash(HashTable *hash);
int insereHash(HashTable *hash, char *palavra, char *documento);
int buscaHash(HashTable *hash, char *palavra, EntradaHash **resultado);
void imprimeHash(HashTable *hash);

#endif // HASH_H
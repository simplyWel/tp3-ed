#ifndef HASH_H
#define HASH_H

#define MAX_DOCUMENTOS 100 // Número máximo de documentos
#define MAX_TAMANHO_PALAVRA 20 // Tamanho máximo de uma palavra
#define MAX_TAMANHO_DOCUMENTO 50 // Tamanho máximo de um nome de documento   
#define MAX_TAMANHO_VOCABULARIO 1000 // Tamanho máximo do vocabulário
#define MAX_PALAVRAS_BUSCADAS 100 // Número máximo de palavras buscadas
#define MAX_PALAVRAS_POR_DOCUMENTO 1000 // Número máximo de palavras por documento
#define MAX_TAMANHO_LINHA 1000 // Tamanho máximo de uma linha


typedef struct {
    char palavra[MAX_TAMANHO_PALAVRA + 1];
    char documentos[MAX_DOCUMENTOS][MAX_DOCUMENTOS + 1];
    int qtdDocumentos;
} EntradaHash;

typedef struct {
    EntradaHash *tabela;
    int tamanho;
} HashTable;




int hashFunction(char *chave, int m);
HashTable* criaHash(int tamanho);
void liberaHash(HashTable *hash);
int insereHash(HashTable *hash, char *palavra, char *documento);
int buscaHash(HashTable *hash, char *palavra, EntradaHash **resultado);
void imprimeHash(HashTable *hash);
int comparaEntradas(const void *a, const void *b);
void ordenaPalavras(HashTable *indice);
void insereDocumento(char *palavra, char *documento);

#endif // HASH_H
#ifndef INDICEINVERTIDO_H
#define INDICEINVERTIDO_H


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

HashTable* aloca(int tamanho);
void libera(HashTable *indice);
int busca(HashTable *hash, char *palavra, EntradaHash **resultado);
void consulta(HashTable *indice, char **palavras, int qtdPalavras);
void insereDocumento(HashTable *indice, char *palavra, char *documento);
void imprime(HashTable *indice);
void lePalavra(HashTable *indice);
void quickSort(char **documentos, int inicio, int fim);
int particiona(char **documentos, int inicio, int fim);

#endif // INDICEINVERTIDO_H
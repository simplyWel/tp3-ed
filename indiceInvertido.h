#ifndef INDICEINVERTIDO_H
#define INDICEINVERTIDO_H
#include <stdio.h>
#include "hash.h"

#define MAX_DOCUMENTOS 100
#define MAX_PALAVRAS_BUSCADAS 100
#define MAX_PALAVRAS_POR_DOCUMENTO 1000
#define MAX_VOCABULARIO 1000
#define MAX_TAMANHO_PALAVRA 20
#define MAX_TAMANHO_DOCUMENTO 50

typedef struct {
    char palavra[20];
    char documentos[100][100];
    int totalDoc;
} EntradaIndice;

typedef struct {
    EntradaIndice *entradas;
    int totalEntradas;
} IndiceInvertido;

void ordenaPalavras(HashTable *indice);


// aloca o TAD IndiceInvertido


// libera o TAD IndiceInvertido
void libera(HashTable *indice);

void ordenaDocumentos(EntradaHash *entrada);

// insere um documento baseado na chave no TAD IndiceInvertido
void insereDocumento(char *palavra, char *documento);

// retorna o índice de uma chave no TAD IndiceInvertido
int busca(char *palavra);

// Baseado em uma ou mais chaves, retorna o nome dos documentos que contêm todas as chaves no índice invertido presente no TAD IndiceInvertido
void consulta(HashTable *indice, char **palavras, int qtdPalavras);

// imprime o índice invertido presente no TAD IndiceInvertido
void imprime(HashTable *indice);

// insere uma palavra e associa um documento
void inserePalavra(char *palavra, char *documento);

#endif // INDICEINVERTIDO_H
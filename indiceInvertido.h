#ifndef INDICEINVERTIDO_H
#define INDICEINVERTIDO_H
#include <stdio.h>
#include "hash.h"

typedef struct {
    char palavra[20];
    char documentos[100][100];
    int totalDoc;
} EntradaIndice;

typedef struct {
    EntradaIndice *entradas;
    int totalEntradas;
} IndiceInvertido;

// aloca o TAD IndiceInvertido
HashTable* aloca(int tamanho);

// libera o TAD IndiceInvertido
void libera(HashTable *indice);

// insere um documento baseado na chave no TAD IndiceInvertido
void insereDocumento(char *palavra, char *documento);

// retorna o índice de uma chave no TAD IndiceInvertido
int busca(char *palavra);

// Baseado em uma ou mais chaves, retorna o nome dos documentos que contêm todas as chaves no índice invertido presente no TAD IndiceInvertido
void consulta(char **palavras, int qtdPalavras);

// imprime o índice invertido presente no TAD IndiceInvertido
void imprime(HashTable *indice);

// insere uma palavra e associa um documento
void inserePalavra(char *palavra, char *documento);

#endif // INDICEINVERTIDO_H
#ifndef INDICEINVERTIDO_H
#define INDICEINVERTIDO_H
#include <stdio.h>
#include "hash.h"

// aloca o TAD IndiceInvertido e inicializa o índice invertido


// libera o TAD IndiceInvertido
void libera(HashTable *indice);

void ordenaDocumentos(EntradaHash *entrada);

HashTable* aloca(int tamanho);

// retorna o índice de uma chave no TAD IndiceInvertido
int busca(char *palavra);

// Baseado em uma ou mais chaves, retorna o nome dos documentos que contêm todas as chaves no índice invertido presente no TAD IndiceInvertido
void consulta(HashTable *indice, char **palavras, int qtdPalavras);

// imprime o índice invertido presente no TAD IndiceInvertido
void imprime(HashTable *indice);

// insere uma palavra e associa um documento
void inserePalavra(char *palavra, char *documento);

#endif // INDICEINVERTIDO_H
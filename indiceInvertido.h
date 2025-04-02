#ifndef INDICEINVERTIDO_H
#define INDICEINVERTIDO_H

#include "hash.h"

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
#ifndef INDICEINVERTIDO_H
#define INDICEINVERTIDO_H
#include <stdio.h>

// aloca o TAD IndiceInvertido
void aloca();

// libera o TAD IndiceInvertido
void libera();

// insere um documento baseado na chave no TAD IndiceInvertido
void insereDocumento();

// retorna o índice de uma chave no TAD IndiceInvertido
void busca();

// Baseado em uma ou mais chaves, retorna o nome dos documentos que contêm todas as chaves no índice invertido presente no TAD IndiceInvertido
void consulta();

// imprime o índice invertido presente no TAD IndiceInvertido
void imprime();

#endif // INDICEINVERTIDO_H
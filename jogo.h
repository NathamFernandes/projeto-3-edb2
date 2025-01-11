#ifndef JOGO_H
#define JOGO_H

#include "trie.h"
#include "avl.h"

typedef struct
{
    char **grid;
    int altura, largura;
} Tabuleiro;

Tabuleiro ler_tabuleiro(const char *filename);
int ler_palavras(const char *filename, No_TRIE *trie);
void buscar_sequencia(const char *vetor, size_t tamanho, No_TRIE *trie, No_AVL **avl, size_t inicio);
void buscar_palavras(No_TRIE *trie, No_AVL **avl, Tabuleiro tabuleiro);
void imprimir_tabuleiro(const Tabuleiro tabuleiro);
void imprimir_resultados(No_AVL *raiz);

#endif

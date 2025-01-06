#ifndef TRIE_H
#define TRIE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define ALFABETO 26

typedef struct No_TRIE
{
    struct No_TRIE *filhos[ALFABETO];
    bool fim_da_palavra;
} No_TRIE;

No_TRIE *trie_criar_no();
void trie_inserir(No_TRIE *raiz, const char *palavra);
bool trie_buscar(No_TRIE *raiz, const char *palavra);
void trie_liberar(No_TRIE *raiz);

#endif
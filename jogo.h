#ifndef JOGO_H
#define JOGO_H

#include "trie.h"

char** ler_tabuleiro(const char* filename);
int ler_palavras(const char* filename, No_TRIE* trie);

#endif

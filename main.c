#include "avl.h"
#include "trie.h"
#include "jogo.h"
#include <stdio.h>

int main()
{
    Tabuleiro tab = ler_tabuleiro("tabuleiro.txt");

    No_TRIE *trie = trie_criar_no();
    No_AVL *avl = NULL;

    int s = ler_palavras("palavras.txt", trie);

    int a = buscar_palavras(trie, &avl, tab);

    imprimir_resultados(avl);

    trie_liberar(trie);

    return 0;
}

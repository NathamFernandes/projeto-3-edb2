#include "avl.h"
#include "trie.h"
#include "jogo.h"

int main()
{
    char** tab = ler_tabuleiro("tabuleiro.txt");

    for (size_t i = 0; i < 10; i++) {
        for (size_t j = 0; j < 10; j++) {
            printf("%c ", tab[i][j]);
        }
        printf("\n");
    }

    No_TRIE* trie = trie_criar_no();

    int s = ler_palavras("palavras.txt", trie);

    return 0;
}

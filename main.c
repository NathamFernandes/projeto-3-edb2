#include "avl.h"
#include "trie.h"
#include "jogo.h"
#include <stdio.h>

// void printTrie(No_TRIE *root, char *buffer, int depth) {
//     if (root->fim_da_palavra) {
//         buffer[depth] = '\0';
//         printf("%s\n", buffer); // Imprime a palavra completa
//     }
//
//     for (int i = 0; i < ALFABETO; i++) {
//         if (root->filhos[i]) {
//             buffer[depth] = 'a' + i; // Adiciona o caractere ao buffer
//             printTrie(root->filhos[i], buffer, depth + 1);
//         }
//     }
// }

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

#include "jogo.h"
#include "avl.h"
#include "trie.h"

char** ler_tabuleiro(const char* filename) {
    FILE* arq_entrada = fopen(filename, "r");

    if (!arq_entrada)
        return NULL;

    int altura, largura;
    fscanf(arq_entrada, "%d %d", &altura, &largura);

    char** tabuleiro = malloc(altura * sizeof(char*));

    for (size_t i = 0; i < largura; i++)
        tabuleiro[i] = malloc(sizeof(char));

    for (size_t i = 0; i < altura; i++) {
        for (size_t j = 0; j < largura; j++) {
            char ch;
            fscanf(arq_entrada, " %c", &ch);

            tabuleiro[i][j] = ch;
        }
    }

    return tabuleiro;
}

int ler_palavras(const char* filename, No_TRIE* trie) {
    FILE* arq_entrada = fopen(filename, "r");

    if (!arq_entrada) return 1;

    char palavra[MAXSTRLEN];

    while (fscanf(arq_entrada, "%s", palavra) != EOF) {
        trie_inserir(trie, palavra);
    }
    
    return 0;
}

int buscar_palavras(No_TRIE* trie, const char** tabuleiro) {

}

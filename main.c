#include <cstdlib>
#include <stdio.h>
#include "avl.h"
#include "trie.h"
#include "jogo.h"
#include "cmd.h"

int main(int argc, char* argv[])
{
    if (argc == 1 || !strcmp("-h", argv[1])) {
        uso();
        return EXIT_SUCCESS;
    }

    struct runningOpt opt = cmd_converter(argc, argv);

    if (opt.palavra_arq == NULL || opt.tabuleiro_arq == NULL) {
        uso();
        return EXIT_FAILURE;
    }

    No_TRIE *trie = trie_criar_no();
    No_AVL *avl = NULL;
    Tabuleiro tab;

    int status = ler_tabuleiro(opt.tabuleiro_arq, &tab);

    if (status == READ_FAIL)
        return EXIT_FAILURE;

    status = ler_palavras(opt.palavra_arq, trie);

    if (status == READ_FAIL)
        return EXIT_FAILURE;

    int opcao;

    do {
        limpar_tela();
        banner();

        printf("[1] Mostrar tabuleiro\n");
        printf("[2] Procurar palavras no tabuleiro\n");
        printf("[3] Mostrar palavras encontradas no tabuleiro\n");
        printf("[4] Sair do programa\n\n");

        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                limpar_tela();
                imprimir_tabuleiro(tab);
                enter();
                limpar_tela();
                break;
            case 2:
                limpar_tela();
                buscar_palavras(trie, &avl, tab);
                printf("Busca realizada!\n");
                enter();
                limpar_tela();
                break;
            case 3:
                limpar_tela();
                imprimir_resultados(avl);
                enter();
                limpar_tela();
                break;
            case 4:
                terminar_jogo(trie, avl, tab);
                break;
        }
    } 
    while (opcao != 4);

    return EXIT_SUCCESS;
}

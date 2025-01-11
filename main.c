#include <stdio.h>
#include "avl.h"
#include "trie.h"
#include "jogo.h"

struct runningOpt {
    char *palavra_arq;
    char *tabuleiro_arq;
};

void uso()
{
    printf("Usage: caca-palavra [<Options>] <input_files>\n"); 
    printf("   Game options:\n"); 
    printf("      -t        Arquivo de tabuleiro.\n"); 
    printf("      -p        Arquivo de palavras.\n"); 
    printf("      -h        Imprime esta mensagem de uso.\n"); 
}

struct runningOpt cmd_converter(int argc, char* argv[]) {
    struct runningOpt opt;

    opt.palavra_arq = NULL;
    opt.tabuleiro_arq = NULL;

    for (size_t arg = 1; arg < argc; arg++) {
        if (!strcmp(argv[arg], "-t")) {
            if (arg + 1 < argc) {
                opt.tabuleiro_arq = argv[arg + 1];
                arg++;
            }
            else { 
                fprintf(stdout, "Erro: É necessário informar o arquivo de tabuleiro.\n");
                break;
            }
        }
        else if (!strcmp(argv[arg], "-p")) {
            if (arg + 1 < argc) {
                opt.palavra_arq = argv[arg + 1];
                arg++;
            }
            else {
                fprintf(stdout, "Erro: É necessário informar o arquivo de palavras.\n");
                break;
            }
        }
        else {
            fprintf(stdout, "Error: O comando \'%s\' nao e reconhecido.\n", argv[arg]);
            opt.palavra_arq = NULL;
            opt.tabuleiro_arq = NULL;

            break;
        }
    }

    return opt;
}

void banner()
{
    printf("\n");
    printf("+-------------------------------------------------------------------+\n");
    printf("|                                       _                           |\n");
    printf("|  ___ __ _  ___ __ _       _ __   __ _| | __ ___   ___ __ __ _ ___ |\n");
    printf("| / __/ _` |/ __/ _` |_____| '_ \\ / _` | |/ _` \\ \\ / / '__/ _` / __||\n");
    printf("|| (_| (_| | (_| (_| |_____| |_) | (_| | | (_| |\\ V /| | | (_| \\__ \\|\n");
    printf("| \\___\\__,_|\\___\\__,_|     | .__/ \\__,_|_|\\__,_| \\_/ |_|  \\__,_|___/|\n");
    printf("|                          |_|                                      |\n");
    printf("+-------------------------------------------------------------------+\n");
    printf("\n");
}

void limpar_tela() 
{
#if defined(_WIN32) || defined(_WIN64)
    system("cls");
#else
    system("clear");
#endif
}

void enter() {
    getc(stdin);
    char enter;

    while (enter != '\n') {
        enter = getchar();
    }
}

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

    Tabuleiro tab = ler_tabuleiro(opt.tabuleiro_arq);
    int s = ler_palavras(opt.palavra_arq, trie);

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
                trie_liberar(trie);
                break;
        }
    } 
    while (opcao != 4);

    return 0;
}

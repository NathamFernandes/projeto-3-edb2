#include <stdio.h>
#include <string.h>

#include "cmd.h"

/**
 * @brief Exibe a mensagem de uso para o programa de caça-palavras.
 * 
 * Mostra as opções disponíveis e o formato esperado para os arquivos de entrada.
 */
void uso()
{
    printf("Usage: caca-palavra [<Options>] <input_files>\n"); 
    printf("   Game options:\n"); 
    printf("      -t        Arquivo de tabuleiro.\n"); 
    printf("      -p        Arquivo de palavras.\n"); 
    printf("      -h        Imprime esta mensagem de uso.\n"); 
}

/**
 * @brief Processa os argumentos de linha de comando e converte-os para opções executáveis.
 * 
 * @param argc Número de argumentos passados na linha de comando.
 * @param argv Array de strings representando os argumentos passados.
 * 
 * @return Estrutura runningOpt contendo os caminhos para os arquivos de tabuleiro e palavras.
 *         Se algum erro ocorrer, os valores serão NULL.
 */
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

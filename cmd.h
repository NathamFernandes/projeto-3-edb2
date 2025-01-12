#ifndef CMD_H
#define CMD_H

// Estrutura para armazenar os caminhos dos arquivos de palavras e tabuleiro
// informados via linha de comando.
struct runningOpt {
    char *palavra_arq;   // Caminho para o arquivo de palavras.
    char *tabuleiro_arq; // Caminho para o arquivo de tabuleiro.
};

// Exibe a mensagem de uso do programa com as opções disponíveis.
void uso();

// Converte os argumentos da linha de comando em opções executáveis.
struct runningOpt cmd_converter(int argc, char* argv[]);

#endif

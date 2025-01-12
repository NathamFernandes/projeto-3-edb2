#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include "jogo.h"
#include "avl.h"
#include "trie.h"

/**
 * @brief Lê um tabuleiro de um arquivo e retorna sua estrutura.
 *
 * O arquivo deve conter as dimensões do tabuleiro na primeira linha (altura e largura),una
 * seguidas pelas linhas do tabuleiro contendo caracteres.
 *
 * @param filename Nome do arquivo de entrada.
 * @return Tabuleiro Estrutura do tabuleiro preenchida com os dados do arquivo.
 */
int ler_tabuleiro(const char *filename, Tabuleiro *tabuleiro)
{
    FILE *arq_entrada = fopen(filename, "r");

    if (!arq_entrada) {
        fprintf(stdout, "Falha ao buscar o arquivo \"%s\": %s.\n", filename, strerror(errno));
        return READ_FAIL;
    }

    fscanf(arq_entrada, "%zu %zu", &tabuleiro->altura, &tabuleiro->largura);

    // Aloca memória para o grid do tabuleiro
    tabuleiro->grid = (Letra**) malloc(tabuleiro->altura * sizeof(Letra *));

    for (size_t i = 0; i < tabuleiro->largura; i++)
    {
        tabuleiro->grid[i] = malloc(tabuleiro->largura * sizeof(Letra));
    }

    // Preenche o grid do tabuleiro com os caracteres do arquivo
    for (size_t i = 0; i < tabuleiro->altura; i++)
    {
        for (size_t j = 0; j < tabuleiro->largura; j++)
        {
            char ch;
            fscanf(arq_entrada, " %c", &ch);
            tabuleiro->grid[i][j].letra = ch;
            tabuleiro->grid[i][j].linha = i;
            tabuleiro->grid[i][j].coluna = j;
        }
    }

    fclose(arq_entrada);

    return READ_OK;
}

/**
 * @brief Lê palavras de um arquivo e insere em uma estrutura TRIE.
 *
 * Cada linha do arquivo deve conter uma palavra. As palavras são inseridas
 * em uma TRIE para buscas rápidas.
 *
 * @param filename Nome do arquivo de entrada.
 * @param trie Ponteiro para a estrutura TRIE.
 * @return int 0 se bem-sucedido, 1 se ocorrer erro ao abrir o arquivo.
 */
int ler_palavras(const char *filename, No_TRIE *trie)
{
    FILE *arq_entrada = fopen(filename, "r");
    if (!arq_entrada) {
        fprintf(stdout, "Falha ao buscar o arquivo \"%s\": %s.\n", filename, strerror(errno));
        return READ_FAIL;
    }

    char palavra[MAXSTRLEN];

    // Lê palavras linha a linha e as insere na TRIE
    while (fscanf(arq_entrada, "%s", palavra) != EOF)
    {
        trie_inserir(trie, palavra);
    }

    fclose(arq_entrada);

    return READ_OK;
}

/**
 * @brief Inverte uma palavra e retorna uma nova string com o conteúdo invertido.
 *
 * @param palavra String de entrada a ser invertida.
 * @return char* Nova string contendo a palavra invertida.
 */
static char *palavra_invertida(const char *palavra)
{
    size_t tamanho = strlen(palavra);
    char *invertida = malloc(tamanho + 1 * sizeof(char));

    for (size_t i = 0; i < tamanho; i++)
    {
        invertida[i] = palavra[tamanho - i - 1];
    }

    invertida[tamanho] = '\0';

    return invertida;
}

/**
 * @brief Busca palavras de uma sequência horizontal, vertical, ou diagonal em um vetor de caracteres.
 *
 * A função verifica todas as substrings do vetor e busca por palavras
 * normais e invertidas na TRIE, inserindo-as em uma AVL se encontradas.
 *
 * @param vetor Vetor de caracteres representando uma linha, coluna, ou diagonal.
 * @param tamanho Tamanho do vetor.
 * @param trie Ponteiro para a estrutura TRIE.
 * @param avl Ponteiro para a raiz da AVL.
 */
void buscar_sequencia(const Letra *vetor, size_t tamanho, No_TRIE *trie, No_AVL **avl)
{
    char substring[tamanho + 1];

    for (size_t i = 0; i < tamanho; i++)
    {
        size_t length = 0;
        substring[length++] = vetor[i].letra;

        // Checa em ambos os sentidos todas as possibilidades de palavras
        for (size_t j = i + 1; j < tamanho; j++)
        {
            substring[length++] = vetor[j].letra;
            substring[length] = '\0';

            char *substring_invertida = palavra_invertida(substring);
            Palavra p;

            if (trie_buscar(trie, substring))
            {
                strcpy(p.palavra, substring);

                p.x1 = vetor[i].linha;
                p.y1 = vetor[i].coluna;

                p.x2 = vetor[j].linha;
                p.y2 = vetor[j].coluna;

                (*avl) = avl_inserir_no(*avl, p);
                break;
            }

            if (trie_buscar(trie, substring_invertida))
            {
                strcpy(p.palavra, substring_invertida);

                p.x1 = vetor[j].linha;
                p.y1 = vetor[j].coluna;

                p.x2 = vetor[i].linha;
                p.y2 = vetor[i].coluna;

                (*avl) = avl_inserir_no(*avl, p);
                break;
            }

            free(substring_invertida);
        }
    }
}

/**
 * @brief Busca palavras no tabuleiro em todas as direções.
 *
 * A função analisa as linhas e colunas do tabuleiro em busca de palavras
 * na TRIE, inserindo-as em uma AVL se encontradas.
 *
 * @param trie Ponteiro para a estrutura TRIE.
 * @param avl Ponteiro para a raiz da AVL.
 * @param tabuleiro Estrutura representando o tabuleiro.
 */
void buscar_palavras(No_TRIE *trie, No_AVL **avl, Tabuleiro tabuleiro)
{
    // Busca horizontal nas linhas do tabuleiro
    for (size_t i = 0; i < tabuleiro.altura; i++)
    {
        Letra letras[tabuleiro.altura];
        size_t length = 0;

        for (size_t j = 0; j < tabuleiro.largura; j++) {
            Letra l;
            l.letra = tabuleiro.grid[i][j].letra;
            l.linha = tabuleiro.grid[i][j].linha;
            l.coluna = tabuleiro.grid[i][j].coluna;

            letras[length++] = l;
        }

        buscar_sequencia(letras, tabuleiro.altura, trie, avl);
    }

    // Busca vertical nas colunas do tabuleiro
    for (size_t c = 0; c < tabuleiro.largura; c++)
    {
        Letra temp[tabuleiro.altura];

        for (size_t l = 0; l < tabuleiro.altura; l++)
        {
            Letra letra;
            letra.letra = tabuleiro.grid[l][c].letra;
            letra.linha = tabuleiro.grid[l][c].linha;
            letra.coluna = tabuleiro.grid[l][c].coluna;

            temp[l] = letra;
        }

        buscar_sequencia(temp, tabuleiro.largura, trie, avl);
    }

    // Primeira parte, busca diagonais secundárias da linha 0, das colunas 0 até 9.
    for (size_t coluna = 0; coluna < tabuleiro.largura; coluna++)
    {
        int aux = coluna;
        int length = 0;
        Letra temp[tabuleiro.largura];

        for (size_t linha = 0; linha <= coluna; linha++)
        {
            Letra l;
            l.letra = tabuleiro.grid[linha][aux].letra;
            l.linha = tabuleiro.grid[linha][aux].linha;
            l.coluna = tabuleiro.grid[linha][aux].coluna;

            temp[length++] = l;
            aux--;
        }

        buscar_sequencia(temp, length, trie, avl);
    }

    // Segunda parte, busca diagonais secundárias da coluna 9, das linhas 1 até 9.
    for (size_t linha = 1; linha < tabuleiro.altura; linha++)
    {
        int aux = linha;
        int length = 0;
        Letra temp[tabuleiro.largura];

        for (size_t coluna = 9; aux <= 9; coluna--)
        {
            Letra l;
            l.letra = tabuleiro.grid[aux][coluna].letra;
            l.linha = tabuleiro.grid[aux][coluna].linha;
            l.coluna = tabuleiro.grid[aux][coluna].coluna;

            temp[length++] = l;
            aux++;
        }

        buscar_sequencia(temp, length, trie, avl);
    }

    // Terceira parte, busca diagonais principais da linha 0, das colunas 9 até 0.
    for (int coluna = 9; coluna >= 0; --coluna)
    {
        int aux = coluna;
        int length = 0;
        Letra temp[tabuleiro.altura];

        for (size_t linha = 0; linha < 10 - coluna; linha++)
        {
            Letra l;
            l.letra = tabuleiro.grid[linha][aux].letra;
            l.linha = tabuleiro.grid[linha][aux].linha;
            l.coluna = tabuleiro.grid[linha][aux].coluna;

            temp[length++] = l;
            aux++;
        }

        buscar_sequencia(temp, length, trie, avl);
    }

    // Quarta parte, busca diagonais principais da coluna 0, das linhas 1 até 9.
    for (size_t linha = 1; linha < tabuleiro.altura; linha++)
    {
        int aux = linha;
        int length = 0;
        Letra temp[tabuleiro.largura];

        for (size_t coluna = 0; coluna < tabuleiro.largura - linha; coluna++)
        {
            Letra l;
            l.letra = tabuleiro.grid[aux][coluna].letra;
            l.linha = tabuleiro.grid[aux][coluna].linha;
            l.coluna = tabuleiro.grid[aux][coluna].coluna;

            temp[length++] = l;
            aux++;
        }

        buscar_sequencia(temp, length, trie, avl);
    }
}

/**
 * @brief Imprime os resultados armazenados na árvore AVL.
 * 
 * Esta função chama a função auxiliar `avl_imprimir_em_ordem` para percorrer
 * e imprimir os elementos da árvore AVL em ordem.
 * 
 * @param raiz Ponteiro para o nó raiz da árvore AVL.
 */
void imprimir_resultados(No_AVL *raiz)
{
    avl_imprimir_em_ordem(raiz);
}

/**
 * @brief Imprime o tabuleiro do jogo no formato visual.
 * 
 * @param tabuleiro Estrutura contendo o grid do tabuleiro e suas dimensões.
 */
void imprimir_tabuleiro(const Tabuleiro tabuleiro)
{
    for (size_t i = 0; i < tabuleiro.largura * 2 + 1; i++)
        printf("-");
    printf("\n");

    for (size_t l = 0; l < tabuleiro.altura; l++) {
        printf("|");
        for (size_t c = 0; c < tabuleiro.largura; c++) {
            char ch = toupper(tabuleiro.grid[l][c].letra);
            
            printf("%c ", ch);
        }
        printf("\b|");
        printf("\n");
    }

    for (size_t i = 0; i < tabuleiro.largura * 2 + 1; i++)
        printf("-");
    printf("\n");
}

/**
 * @brief Exibe o banner do jogo na saída padrão.
 */
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

/**
 * @brief Limpa a tela do console, dependendo do sistema operacional.
 */
void limpar_tela() 
{
#if defined(_WIN32) || defined(_WIN64)
    system("cls");
#else
    system("clear");
#endif
}

/**
 * @brief Aguarda o usuário pressionar a tecla Enter.
 */
void enter()
{
    getc(stdin);
    char enter;

    while (enter != '\n') {
        enter = getchar();
    }
}

/**
 * @brief Libera todos os recursos alocados e encerra o jogo.
 * 
 * @param trie Ponteiro para a estrutura TRIE a ser liberada.
 * @param avl Ponteiro para a árvore AVL a ser liberada.
 * @param tabuleiro Estrutura contendo o tabuleiro que será liberado.
 */
void terminar_jogo(No_TRIE *trie, No_AVL* avl, Tabuleiro tabuleiro)
{
    trie_liberar(trie);
    avl_liberar_arvore(avl);

    for (size_t l = 0; l < tabuleiro.altura; l++)
        free(tabuleiro.grid[l]);

    free(tabuleiro.grid);
}

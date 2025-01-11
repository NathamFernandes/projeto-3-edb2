#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jogo.h"
#include "avl.h"
#include "trie.h"

/**
 * @brief Lê um tabuleiro de um arquivo e retorna sua estrutura.
 *
 * O arquivo deve conter as dimensões do tabuleiro na primeira linha (altura e largura),
 * seguidas pelas linhas do tabuleiro contendo caracteres.
 *
 * @param filename Nome do arquivo de entrada.
 * @return Tabuleiro Estrutura do tabuleiro preenchida com os dados do arquivo.
 */
Tabuleiro ler_tabuleiro(const char *filename)
{
    // Abre o arquivo para leitura
    FILE *arq_entrada = fopen(filename, "r");
    Tabuleiro tabuleiro;

    // Lê as dimensões do tabuleiro
    fscanf(arq_entrada, "%d %d", &tabuleiro.altura, &tabuleiro.largura);

    // Aloca memória para o grid do tabuleiro
    tabuleiro.grid = malloc(tabuleiro.altura * sizeof(char *));
    for (size_t i = 0; i < tabuleiro.largura; i++)
    {
        tabuleiro.grid[i] = malloc(sizeof(char));
    }

    // Preenche o grid do tabuleiro com os caracteres do arquivo
    for (size_t i = 0; i < tabuleiro.altura; i++)
    {
        for (size_t j = 0; j < tabuleiro.largura; j++)
        {
            char ch;
            fscanf(arq_entrada, " %c", &ch);
            tabuleiro.grid[i][j] = ch;
        }
    }

    // Fecha o arquivo
    fclose(arq_entrada);

    return tabuleiro;
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
    // Abre o arquivo para leitura
    FILE *arq_entrada = fopen(filename, "r");
    if (!arq_entrada)
        return 1; // Retorna erro se o arquivo não for aberto

    char palavra[MAXSTRLEN];

    // Lê palavras linha a linha e as insere na TRIE
    while (fscanf(arq_entrada, "%s", palavra) != EOF)
    {
        trie_inserir(trie, palavra);
    }

    // Fecha o arquivo
    fclose(arq_entrada);

    return 0;
}

/**
 * @brief Inverte uma palavra e retorna uma nova string com o conteúdo invertido.
 *
 * @param palavra String de entrada a ser invertida.
 * @return char* Nova string contendo a palavra invertida.
 */
static char *palavra_invertida(const char *palavra)
{
    // Calcula o tamanho da palavra
    size_t tamanho = strlen(palavra);

    // Aloca memória para a string invertida
    char *invertida = malloc(tamanho + 1 * sizeof(char));

    // Copia os caracteres em ordem inversa
    for (size_t i = 0; i < tamanho; i++)
    {
        invertida[i] = palavra[tamanho - i - 1];
    }

    // Adiciona o terminador nulo
    invertida[tamanho] = '\0';

    return invertida;
}

/**
 * @brief Busca palavras horizontalmente em um vetor de caracteres.
 *
 * A função verifica todas as substrings do vetor e busca por palavras
 * normais e invertidas na TRIE, inserindo-as em uma AVL se encontradas.
 *
 * @param vetor Vetor de caracteres representando uma linha.
 * @param tamanho Tamanho do vetor.
 * @param trie Ponteiro para a estrutura TRIE.
 * @param avl Ponteiro para a raiz da AVL.
 */
void buscar_horizontal(const char *vetor, size_t tamanho, No_TRIE *trie, No_AVL **avl)
{
    char substring[tamanho + 1];

    for (size_t i = 0; i < tamanho; i++)
    {
        size_t length = 0;
        substring[length++] = vetor[i];

        int index = vetor[i] - 'a';
        // if (trie->filhos[index] == NULL)
        //     continue;

        for (size_t j = i + 1; j < tamanho; j++)
        {
            substring[length++] = vetor[j];
            substring[length] = '\0';

            char *substring_invertida = palavra_invertida(substring);
            Palavra p;

            if (trie_buscar(trie, substring))
            {
                strcpy(p.palavra, substring);
                p.linha = i;
                p.coluna = j;

                (*avl) = avl_inserir_no(*avl, p);
                break;
            }

            if (trie_buscar(trie, substring_invertida))
            {
                strcpy(p.palavra, substring_invertida);
                p.linha = i;
                p.coluna = j;

                (*avl) = avl_inserir_no(*avl, p);
                break;
            }

            free(substring_invertida);
        }
    }
}

/**
 * @brief Busca palavras verticalmente em um vetor de caracteres.
 *
 * @param vetor Vetor de caracteres representando uma coluna.
 * @param tamanho Tamanho do vetor.
 * @param trie Ponteiro para a estrutura TRIE.
 * @param avl Ponteiro para a raiz da AVL.
 */
void buscar_vertical(const char *vetor, size_t tamanho, No_TRIE *trie, No_AVL **avl)
{
    char substring[tamanho + 1];

    for (size_t i = 0; i < tamanho; i++)
    {
        size_t length = 0;
        substring[length++] = vetor[i];

        int index = vetor[i] - 'a';
        // if (trie->filhos[index] == NULL)
        //     continue;

        for (size_t j = i + 1; j < tamanho; j++)
        {
            substring[length++] = vetor[j];
            substring[length] = '\0';

            char *substring_invertida = palavra_invertida(substring);
            Palavra p;

            if (trie_buscar(trie, substring))
            {
                strcpy(p.palavra, substring);

                (*avl) = avl_inserir_no(*avl, p);
            }

            if (trie_buscar(trie, substring_invertida))
            {
                strcpy(p.palavra, substring_invertida);

                (*avl) = avl_inserir_no(*avl, p);
            }

            p.linha = i;
            p.coluna = j;

            free(substring_invertida);
        }
    }
}

void buscar_diagonal(const char *vetor, size_t tamanho, No_TRIE *trie, No_AVL **avl)
{
    char substring[tamanho + 1];

    for (size_t i = 0; i < tamanho; i++)
    {
        size_t length = 0;
        substring[length++] = vetor[i];

        int index = vetor[i] - 'a';
        // if (trie->filhos[index] == NULL)
        //     continue;

        for (size_t j = i + 1; j < tamanho; j++)
        {
            substring[length++] = vetor[j];
            substring[length] = '\0';

            char *substring_invertida = palavra_invertida(substring);
            Palavra p;

            if (trie_buscar(trie, substring))
            {
                strcpy(p.palavra, substring);

                (*avl) = avl_inserir_no(*avl, p);
            }

            if (trie_buscar(trie, substring_invertida))
            {
                strcpy(p.palavra, substring_invertida);

                (*avl) = avl_inserir_no(*avl, p);
            }

            p.linha = i;
            p.coluna = j;

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
 * @return int 1 ao concluir a busca.
 */
int buscar_palavras(No_TRIE *trie, No_AVL **avl, Tabuleiro tabuleiro)
{
    // Busca horizontal nas linhas do tabuleiro
    for (size_t i = 0; i < tabuleiro.altura; i++)
    {
        buscar_horizontal(tabuleiro.grid[i], tabuleiro.altura, trie, avl);
    }

    // Busca vertical nas colunas do tabuleiro
    for (size_t c = 0; c < tabuleiro.largura; c++)
    {
        char temp[10];

        for (size_t l = 0; l < tabuleiro.altura; l++)
        {
            temp[l] = tabuleiro.grid[l][c];
        }

        buscar_vertical(temp, tabuleiro.largura, trie, avl);
    }

    // Primeira parte, diagonais secundárias (diagonais secundárias que começam com coluna 0 até 9)
    for (size_t coluna = 0; coluna < tabuleiro.largura; coluna++)
    {
        int aux = coluna;
        int length = 0;
        char temp[10];

        for (size_t linha = 0; linha <= coluna; linha++)
        {
            temp[length++] = tabuleiro.grid[linha][aux];
            aux--;
        }

        buscar_diagonal(temp, length, trie, avl);
    }

    // Segunda parte, diagonais secundárias (diagonais secundárias que começam com linha 1 até 9)
    for (size_t linha = 1; linha < tabuleiro.altura; linha++)
    {
        int aux = linha;
        int length = 0;
        char temp[10];

        for (size_t coluna = 9; aux <= 9; coluna--)
        {
            temp[length++] = tabuleiro.grid[aux][coluna];
            aux++;
        }

        buscar_diagonal(temp, length, trie, avl);
    }

    // Terceira parte, diagonais primárias (diagonais primárias que começam com coluna 9 até 0)
    for (int coluna = 9; coluna >= 0; --coluna)
    {
        int aux = coluna;
        int length = 0;
        char temp[10];

        for (size_t linha = 0; linha < 10 - coluna; linha++)
        {
            temp[length++] = tabuleiro.grid[linha][aux];
            aux++;
        }

        buscar_diagonal(temp, length, trie, avl);
    }

    // Quarta parte, diagonais primárias (diagonais primárias que começam com linhas de 1 até 9)
    for (size_t linha = 1; linha < tabuleiro.altura; linha++)
    {
        int aux = linha;
        int length = 0;
        char temp[10];

        for (size_t coluna = 0; coluna < 10 - linha; coluna++)
        {
            temp[length++] = tabuleiro.grid[aux][coluna];
            aux++;
        }

        buscar_diagonal(temp, length, trie, avl);
    }

    return 1;
}

void imprimir_resultados(No_AVL *raiz)
{
    avl_imprimir_em_ordem(raiz);
}

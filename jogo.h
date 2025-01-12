#ifndef JOGO_H
#define JOGO_H

#include "trie.h"
#include "avl.h"

#define READ_OK 0
#define READ_FAIL 1

// Representa uma letra no tabuleiro do jogo.
typedef struct {
    char letra;       // Letra armazenada.
    size_t linha;     // Linha onde a letra está localizada.
    size_t coluna;    // Coluna onde a letra está localizada.
} Letra;

// Estrutura que representa o tabuleiro do jogo.
typedef struct
{
    Letra **grid;        // Matriz de caracteres representando o tabuleiro.
    size_t altura;       // Altura do tabuleiro.
    size_t largura;      // Largura do tabuleiro.
} 
Tabuleiro;

// Lê o tabuleiro do arquivo especificado e preenche a estrutura Tabuleiro.
int ler_tabuleiro(const char *filename, Tabuleiro *tabuleiro);

// Lê as palavras de um arquivo e insere na TRIE.
int ler_palavras(const char *filename, No_TRIE *trie);

// Busca sequências de caracteres no vetor e insere palavras válidas na AVL.
void buscar_sequencia(const Letra *vetor, size_t tamanho, No_TRIE *trie, No_AVL **avl);

// Busca palavras no tabuleiro e insere na AVL as encontradas na TRIE.
void buscar_palavras(No_TRIE *trie, No_AVL **avl, Tabuleiro tabuleiro);

// Imprime o tabuleiro na saída padrão.
void imprimir_tabuleiro(const Tabuleiro tabuleiro);

// Imprime os resultados armazenados na AVL.
void imprimir_resultados(No_AVL *raiz);

// Libera todos os recursos utilizados e encerra o jogo.
void terminar_jogo(No_TRIE *trie, No_AVL* avl, Tabuleiro tabuleiro);

// Exibe o banner do jogo.
void banner();

// Aguarda o usuário pressionar Enter.
void enter();

// Limpa a tela do console.
void limpar_tela();

#endif

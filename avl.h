#ifndef AVL_H
#define AVL_H

#include <stdio.h>
#include <stdlib.h>

#define MAXSTRLEN 20

// Estrutura que representa uma palavra encontrada no tabuleiro.
typedef struct {
    char palavra[MAXSTRLEN]; // Palavra encontrada.
    size_t x1, y1;           // Coordenadas iniciais da palavra no tabuleiro.
    size_t x2, y2;           // Coordenadas finais da palavra no tabuleiro.
} Palavra;

// Nó da árvore AVL, contendo uma palavra e ponteiros para os nós filhos.
typedef struct No_AVL
{
    Palavra dado;           // Palavra armazenada no nó.
    struct No_AVL *esquerdo; // Ponteiro para o filho esquerdo.
    struct No_AVL *direito;  // Ponteiro para o filho direito.
    int altura;             // Altura do nó na árvore.
} No_AVL;

// Retorna a altura de um nó na árvore AVL.
int avl_obter_altura(No_AVL *no);

// Calcula o fator de balanceamento de um nó na árvore AVL.
int avl_calcular_fator_de_balanceamento(No_AVL *no);

// Cria um novo nó AVL com os dados fornecidos.
No_AVL *avl_criar_no(const Palavra dado);

// Realiza uma rotação à direita em torno de um nó na AVL.
No_AVL *avl_rotacao_direita(No_AVL *y);

// Realiza uma rotação à esquerda em torno de um nó na AVL.
No_AVL *avl_rotacao_esquerda(No_AVL *x);

// Insere um novo nó na árvore AVL e mantém o balanceamento.
No_AVL *avl_inserir_no(No_AVL *no, const Palavra dado);

// Retorna o nó com o menor valor na árvore AVL.
No_AVL *avl_menor_valor_no(No_AVL *no);

// Remove um nó da árvore AVL e mantém o balanceamento.
No_AVL *avl_remover_no(No_AVL *raiz, const Palavra dado);

// Imprime os elementos da árvore AVL em ordem crescente.
void avl_imprimir_em_ordem(No_AVL *raiz);

// Libera todos os nós da árvore AVL, desalocando a memória.
void avl_liberar_arvore(No_AVL *raiz);

#endif

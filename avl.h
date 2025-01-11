#ifndef AVL_H
#define AVL_H

#include <stdio.h>
#include <stdlib.h>

#define MAXSTRLEN 20

typedef struct {
    char palavra[MAXSTRLEN];
    size_t x1, y1, x2, y2;
} Palavra;

typedef struct No_AVL
{
    Palavra dado;
    struct No_AVL *esquerdo;
    struct No_AVL *direito;
    int altura;
} No_AVL;

int avl_obter_altura(No_AVL *no);
int avl_calcular_fator_de_balanceamento(No_AVL *no);
No_AVL *avl_criar_no(const Palavra dado);
No_AVL *avl_rotacao_direita(No_AVL *y);
No_AVL *avl_rotacao_esquerda(No_AVL *x);
No_AVL *avl_inserir_no(No_AVL *no, const Palavra dado);
No_AVL *avl_menor_valor_no(No_AVL *no);
No_AVL *avl_remover_no(No_AVL *raiz, const Palavra dado);
void avl_imprimir_em_ordem(No_AVL *raiz);

#endif

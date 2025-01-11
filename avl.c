#include <stdio.h>
#include <string.h>
#include "avl.h"

int avl_obter_altura(No_AVL *no)
{
    if (no == NULL)
        return -1;
    else
        return no->altura;
}

int avl_calcular_fator_de_balanceamento(No_AVL *no)
{
    if (no == NULL)
        return 0;
    else
        return avl_obter_altura(no->esquerdo) - avl_obter_altura(no->direito);
}

No_AVL *avl_criar_no(const Palavra dado)
{
    No_AVL *no = (No_AVL *)malloc(sizeof(No_AVL));
    strcpy(no->dado.palavra, dado.palavra);
    no->dado.x1 = dado.x1;
    no->dado.y1 = dado.y1;
    no->dado.x2 = dado.x2;
    no->dado.y2 = dado.y2;
    no->esquerdo = NULL;
    no->direito = NULL;
    no->altura = 0;

    return no;
}

No_AVL *avl_rotacao_direita(No_AVL *y)
{
    No_AVL *x = y->esquerdo;
    No_AVL *z = x->direito;

    x->direito = y;
    y->esquerdo = z;

    if (avl_obter_altura(y->esquerdo) > avl_obter_altura(y->direito))
        y->altura = 1 + avl_obter_altura(y->esquerdo);
    else
        y->altura = 1 + avl_obter_altura(y->direito);

    if (avl_obter_altura(x->esquerdo) > avl_obter_altura(x->direito))
        x->altura = 1 + avl_obter_altura(x->esquerdo);
    else
        x->altura = 1 + avl_obter_altura(x->direito);

    return x;
}

No_AVL *avl_rotacao_esquerda(No_AVL *x)
{
    No_AVL *y = x->direito;
    No_AVL *z = y->esquerdo;

    y->esquerdo = x;
    x->direito = z;

    if (avl_obter_altura(x->esquerdo) > avl_obter_altura(x->direito))
        x->altura = 1 + avl_obter_altura(x->esquerdo);
    else
        x->altura = 1 + avl_obter_altura(x->direito);
    if (avl_obter_altura(y->esquerdo) > avl_obter_altura(y->direito))
        y->altura = 1 + avl_obter_altura(y->esquerdo);
    else
        y->altura = 1 + avl_obter_altura(y->direito);

    return y;
}

No_AVL *avl_inserir_no(No_AVL *no, const Palavra dado)
{
    if (no == NULL)
        return avl_criar_no(dado);

    if (strcmp(dado.palavra, no->dado.palavra) < 0)
        no->esquerdo = avl_inserir_no(no->esquerdo, dado);
    else if (strcmp(dado.palavra, no->dado.palavra) > 0)
        no->direito = avl_inserir_no(no->direito, dado);
    else
        return no;

    if (avl_obter_altura(no->esquerdo) > avl_obter_altura(no->direito))
        no->altura = 1 + avl_obter_altura(no->esquerdo);
    else
        no->altura = 1 + avl_obter_altura(no->direito);

    int balanceamento = avl_calcular_fator_de_balanceamento(no);

    // Caso 1: Desbalanceamento para a esquerda
    if (balanceamento > 1 && strcmp(dado.palavra, no->esquerdo->dado.palavra) < 0)
        return avl_rotacao_direita(no);

    // Caso 2: Desbalanceamento para a direita
    if (balanceamento < -1 && strcmp(dado.palavra, no->direito->dado.palavra) > 0)
        return avl_rotacao_esquerda(no);

    // Caso 3: Esquerda-Direita
    if (balanceamento > 1 && strcmp(dado.palavra, no->esquerdo->dado.palavra) > 0) {
        no->esquerdo = avl_rotacao_esquerda(no->esquerdo);
        return avl_rotacao_direita(no);
    }

    // Caso 4: Direita-Esquerda
    if (balanceamento < -1 && strcmp(dado.palavra, no->direito->dado.palavra) < 0) {
        no->direito = avl_rotacao_direita(no->direito);
        return avl_rotacao_esquerda(no);
    }

    return no;
}

No_AVL *avl_menor_valor_no(No_AVL *no)
{
    No_AVL *atual = no;

    while (atual->esquerdo != NULL)
        atual = atual->esquerdo;

    return atual;
}

No_AVL *avl_remover_no(No_AVL *raiz, const Palavra dado)
{
    if (raiz == NULL)
        return raiz;

    if (strcmp(dado.palavra, raiz->dado.palavra) < 0)
    {
        raiz->esquerdo = avl_remover_no(raiz->esquerdo, dado);
    }
    else if (strcmp(dado.palavra, raiz->dado.palavra) > 0)
    {
        raiz->direito = avl_remover_no(raiz->direito, dado);
    }
    else
    {
        /* Nó com apenas um filho ou nenhum. */
        if ((raiz->esquerdo == NULL) || (raiz->direito == NULL))
        {
            No_AVL *temp;

            if (raiz->esquerdo != NULL)
                temp = raiz->esquerdo;
            else
                temp = raiz->direito;

            /* Caso de nenhum filho. */
            if (temp == NULL)
            {
                temp = raiz;
                raiz = NULL;
            }
            else
            {
                *raiz = *temp;
            }

            free(temp);
        }
        else
        {
            /* Caso de dois filhos: obtém o sucessor. */
            No_AVL *temp = avl_menor_valor_no(raiz->direito);

            strcpy(raiz->dado.palavra, temp->dado.palavra);

            raiz->direito = avl_remover_no(raiz->direito, temp->dado);
        }
    }

    /* Se a árvore tinha apenas um nó. */
    if (raiz == NULL)
        return raiz;

    if (avl_obter_altura(raiz->esquerdo) > avl_obter_altura(raiz->direito))
        raiz->altura = 1 + avl_obter_altura(raiz->esquerdo);
    else
        raiz->altura = 1 + avl_obter_altura(raiz->direito);

    int balanceamento = avl_calcular_fator_de_balanceamento(raiz);

    /* Caso 1: Desbalanceamento à esquerda. */
    if (balanceamento > 1 && avl_calcular_fator_de_balanceamento(raiz->esquerdo) >= 0)
        return avl_rotacao_direita(raiz);

    /* Caso 2: Desbalanceamento esquerda-direita. */
    if (balanceamento > 1 && avl_calcular_fator_de_balanceamento(raiz->esquerdo) < 0)
    {
        raiz->esquerdo = avl_rotacao_esquerda(raiz->esquerdo);
        return avl_rotacao_direita(raiz);
    }

    /* Caso 3: Desbalanceamento à direita. */
    if (balanceamento < -1 && avl_calcular_fator_de_balanceamento(raiz->direito) <= 0)
        return avl_rotacao_esquerda(raiz);

    /* Caso 4: Desbalanceamento direita-esquerda. */
    if (balanceamento < -1 && avl_calcular_fator_de_balanceamento(raiz->direito) > 0)
    {
        raiz->direito = avl_rotacao_direita(raiz->direito);
        return avl_rotacao_esquerda(raiz);
    }

    return raiz;
}

void avl_imprimir_em_ordem(No_AVL *raiz)
{
    if (raiz != NULL)
    {
        avl_imprimir_em_ordem(raiz->esquerdo);
        printf("Palavra: %s\n", raiz->dado.palavra);
        printf("Inicio -> (%zu, %zu)\n", raiz->dado.x1, raiz->dado.y1);
        printf("Final -> (%zu, %zu)\n", raiz->dado.x2, raiz->dado.y2);
        printf("\n");
        avl_imprimir_em_ordem(raiz->direito);
    }
}

#include "avl.h"
#include "trie.h"

int main()
{
    No_AVL *raiz = NULL;

    raiz = avl_inserir_no(raiz, "OLA");
    raiz = avl_inserir_no(raiz, "BOLA");
    raiz = avl_inserir_no(raiz, "ILHA");

    raiz = avl_remover_no(raiz, "OLA"); 

    avl_imprimir_em_ordem(raiz);

    return 0;
}

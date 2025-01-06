#include "trie.h"

No_TRIE *trie_criar_no()
{
    No_TRIE *novo_no = (No_TRIE *)malloc(sizeof(No_TRIE));

    if (novo_no)
    {
        novo_no->fim_da_palavra = false;
        for (int i = 0; i < ALFABETO; i++)
        {
            novo_no->filhos[i] = NULL;
        }
    }

    return novo_no;
}

void trie_inserir(No_TRIE *raiz, const char *palavra)
{
    No_TRIE *atual = raiz;

    for (int i = 0; palavra[i] != '\0'; i++)
    {
        int indice = palavra[i] - 'a';

        if (atual->filhos[indice] == NULL)
            atual->filhos[indice] = trie_criar_no();

        atual = atual->filhos[indice];
    }

    atual->fim_da_palavra = true;
}

bool trie_buscar(No_TRIE *raiz, const char *palavra)
{
    No_TRIE *atual = raiz;

    for (int i = 0; palavra[i] != '\0'; i++)
    {
        int indice = palavra[i] - 'a';

        if (atual->filhos[indice] == NULL)
            return false;

        atual = atual->filhos[indice];
    }

    return atual->fim_da_palavra;
}

void trie_liberar(No_TRIE *raiz)
{
    if (raiz == NULL)
        return;

    for (int i = 0; i < ALFABETO; i++)
        trie_liberar(raiz->filhos[i]);

    free(raiz);
}
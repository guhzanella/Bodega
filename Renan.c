#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define TAM 30


typedef struct produto
{
    int codigo;
    char nome[TAM];
    float preco;
} TpProduto;

typedef struct nodo
{
    TpProduto info;
    struct nodo *next;
    struct nodo *prev;
} TpNodo;

typedef struct lista
{
    int nItens;
    TpNodo *first;
    TpNodo *last;
} TpLista;

void exibir(TpLista *sentinela)
{
    TpNodo *aux = sentinela->last;

    if(aux == NULL)
        printf("Lista vazia\n");
    else
    {
        printf("Quantidade de produtos: %d\n", sentinela->nItens);
        while(aux != NULL)
        {
            printf("Codigo: %d\n", (aux->info).codigo);
            printf("Nome: %s", (aux->info).nome);
            printf("Preco: %.2f\n\n", (aux->info).preco);
            aux = aux->next;
        }
    }
}

void codigoo(TpLista *sentinela)
{
    TpNodo *aux = sentinela->last;
    if(aux == NULL)
        printf("Lista vazia\n");
    else
    {
        printf("Codigos disponiveis:\n");
        while(aux != NULL)
        {
            printf("Codigo: %d\n", (aux->info).codigo);
            aux = aux->next;
        }
    }
}

TpNodo *inserir(TpNodo *k, TpLista *sentinela)
{
    //Cria um novo nodo
    TpNodo *u = (TpNodo*)malloc(sizeof(TpNodo));

    printf("Informe o codigo do produto: ");
    scanf("%d", &((u->info).codigo));
    __fpurge(stdin);
    printf("Informe o nome do produto: ");
    fgets((u->info).nome, TAM, stdin);
    __fpurge(stdin);
    printf("Informe o preco: ");
    scanf("%f", &((u->info).preco));
    __fpurge(stdin);

    if(sentinela->nItens == 0)    //Isso indica que a lista não tem elementos ainda
    {
        //Coloca o nodo na lista
        u->next = NULL;
        u->prev = k;
        //Gerencia a sentinela
        sentinela->first = u;
        sentinela->last = u;
        sentinela->nItens++;
    }
    //Faz a ligação entre os nodos caso tenha mais elementos
    else
    {
        (sentinela->first)->next = u;
        u->prev = (sentinela->first);
        u->next = NULL;

        sentinela->first = u;
        sentinela->nItens++;
    }
    return u;
}

TpNodo *excluir(TpNodo *k, TpLista *sentinela)
{
    int codigo;
    system("clear || cls");
    codigoo(sentinela);

    if(sentinela->nItens != 0)
    {
        printf("Informe o codigo do produto que sera removido: ");
        scanf("%d", &codigo);
        //Caso existe apenas um elemento na lista
        if(sentinela->nItens == 1)
        {
            if(codigo == ((sentinela->first)->info).codigo)
            {
                TpNodo *aux = sentinela->first;

                sentinela->first = NULL;
                sentinela->last = NULL;
                sentinela->nItens--;
            }
            else
                printf("O codigo %d nao existe na lista.\n", codigo);
        }
        //Caso o elemento a ser removido seja o primeiro
        else if(codigo == ((sentinela->first)->info).codigo)
        {
            TpNodo* aux = (sentinela->first);

            sentinela->first = aux->prev;
            (aux->prev)->next = NULL;
            sentinela->nItens--;
            system("clear || cls");
            printf("O elemento de codigo %d foi removido!\n", codigo);
            free(aux);
        }
        //Caso o elemento a ser removido seja o ultimo
        else if (codigo == ((sentinela->last)->info).codigo)
        {
            TpNodo* aux = (sentinela->last);

            sentinela->last = aux->next;
            (aux->next)->prev = NULL;
            sentinela->nItens--;
            system("clear || cls");
            printf("O elemento de codigo %d foi removido!\n", codigo);
            free(aux);
        }
        //Caso o elemento a ser removido esteja no meio da lista
        else
        {
            TpNodo* aux = (sentinela->last);

            while(aux != NULL)
            {
                if((aux->info).codigo == codigo)
                {
                    (aux->prev)->next = aux->next;
                    (aux->next)->prev = aux->prev;
                    sentinela->nItens--;
                    system("clear || cls");
                    printf("O elemento de codigo %d foi removido!\n", codigo);

                    free(aux);
                    break;
                }
                else
                    aux = aux->next;
            }
            //Caso nao encontre
            if(aux == NULL)
                printf("O codigo %d não existe na lista.\n", codigo);
        }
    }
    return k;
}

int main()
{
    TpNodo *k = NULL;
    TpLista *sentinela = (TpLista*)malloc(sizeof(TpLista));
    sentinela->nItens = 0;
    sentinela->first = NULL;
    sentinela->last = NULL;
    int opcao;

    do
    {
        printf("1- Inserir um produto\n");
        printf("2- Excluir produto\n");
        printf("3- Listar todos os produtos\n");
        printf("0- Sair\n");
        printf("Digite uma opcao: ");
        scanf("%d", &opcao);
        system("clear || cls");
        switch(opcao)
        {
        case 1:
            k = inserir(k, sentinela);
            break;
        case 2:
            k = excluir(k, sentinela);
            break;
        case 3:
            exibir(sentinela);
            break;
        case 0:
            printf("Programa encerrado!\n");
            break;
        }
    }
    while(opcao != 0);

    return 0;
}


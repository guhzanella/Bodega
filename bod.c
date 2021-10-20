#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define TAM_CODE 10
#define TAM_NAME 30

typedef struct drk{
    char code[TAM_CODE];
    char name[TAM_NAME];
    int volume;
    float price;
    int qt_stock;
    int isAlcoholic; // 0 - nope, 1 - yep
} Drink;

typedef struct nodo{
    Drink bebida;
    struct nodo *next;
    struct nodo *prev;
} TpNodo;

typedef struct lista{
    int nItens;
    TpNodo *first;
    TpNodo *last;
} TpLista;

TpNodo *inserir(TpNodo *k, TpLista *sentinela){
    TpNodo *u = (TpNodo*)malloc(sizeof(TpNodo));

    printf("Codigo: ");
    scanf("%s", (u->bebida).code);
    printf("Bebida: ");
    scanf("%s", (u->bebida).name);
    printf("Volume (ml): ");
    scanf("%d", &(u->bebida).volume);
    printf("Preco: ");
    scanf("%f", &(u->bebida).price);
    printf("Quantidade: ");
    scanf("%d", &(u->bebida).qt_stock);
    printf("Alcoolica: ");
    scanf("%d", &(u->bebida).isAlcoholic);

    if(sentinela->nItens == 0){
        //Coloca o nodo na lista
        u->next = NULL;
        u->prev = k;
        //Gerencia a sentinela
        sentinela->first = u;
        sentinela->last = u;
        sentinela->nItens++;
    }else{
        (sentinela->first)->next = u;
        u->prev = (sentinela->first);
        u->next = NULL;

        sentinela->first = u;
        sentinela->nItens++;
    }
    return u;
}

TpNodo *excluir(TpNodo *k, TpLista *sentinela){
    char matricula;

    if(sentinela->nItens != 0){
        printf("Informe o codigo da Bebida que sera removida: ");
        scanf("%s", matricula);

        if(sentinela->nItens == 1){ //Caso existe apenas um elemento na lista
            if(strcmp(matricula, ((sentinela->first)->bebida).code) == ((sentinela->first)->bebida).code){
                TpNodo *aux = sentinela->first;

                sentinela->first = NULL;
                sentinela->last = NULL;
                sentinela->nItens--;
            }
        }
        else if(strcmp(matricula, ((sentinela->first)->bebida).code) == ((sentinela->first)->info).matricula){ //Caso o elemento a ser removido seja o primeiro
            TpNodo* aux = (sentinela->first);

            sentinela->first = aux->prev;
            (aux->prev)->next = NULL;
            sentinela->nItens--;
            free(aux);
        }
        else if (strcmp(matricula, ((sentinela->first)->bebida).code) == ((sentinela->last)->info).matricula){ //Caso o aluno a ser removido seja o ultimo
            TpNodo* aux = (sentinela->last);

            sentinela->last = aux->next;
            (aux->next)->prev = NULL;
            sentinela->nItens--;
            free(aux);
        }
        else{ //Caso o aluno a ser removido esteja no meio da lista
            TpNodo* aux = (sentinela->last);

            while(aux != NULL){
                if((aux->info).matricula == matricula){
                    (aux->prev)->next = aux->next;
                    (aux->next)->prev = aux->prev;
                    sentinela->nItens--;
                    free(aux);
                    break;
                }
                else
                    aux = aux->next;
            }
        }
    }
    return k;
}

void exibir(TpLista *sentinela){
    TpNodo *aux = sentinela->last;

    if(aux == NULL)
        printf("Lista Vazia!\n");
    else{
        while(aux != NULL){
            printf("%d, ", (aux->info).matricula);
            printf("%s, ", (aux->info).nome);
            printf("%02d/%02d/%04d, ", aux->info.nascimento.dia, (aux->info).nascimento.mes, (aux->info).nascimento.ano);
            printf("%.2f\n", (aux->info).media);
            aux = aux->next;
        }
    }
}

int main(){
    TpNodo *k = NULL;
    TpLista *sentinela = (TpLista*)malloc(sizeof(TpLista));
    
    sentinela->nItens = 0;
    sentinela->first = NULL;
    sentinela->last = NULL;
    
    int opcao;

    do
    {
        scanf("%d", &opcao);
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
        case 4:
            exibir_ordem_inv(sentinela);
            break;
        case 0:
            break;
        }
    }
    while(opcao != 0);

    return 0;
}

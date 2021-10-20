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
    system("clear || cls");

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
    char codigo[TAM_CODE];
    TpNodo *aux;
    system("clear || cls");

    if(sentinela->nItens != 0){
        printf("Informe o codigo da Bebida que sera removida: ");
        scanf("%s", codigo);

        if(sentinela->nItens == 1){ //Caso existe apenas uma bebida na lista
            if(strcmp(codigo, (aux->bebida).code) == ((sentinela->first)->bebida).code){
                TpNodo *aux = (sentinela->first);

                sentinela->first = NULL;
                sentinela->last = NULL;
                sentinela->nItens--;
            }
        }
        else if(strcmp(codigo, (aux->bebida).code) == ((sentinela->first)->bebida).code){ //Caso a bebida a ser removido seja o primeiro
            TpNodo* aux = (sentinela->first);

            sentinela->first = aux->prev;
            (aux->prev)->next = NULL;
            sentinela->nItens--;
            free(aux);
        }
        else if (strcmp(codigo, (aux->bebida).code) == ((sentinela->last)->bebida).code){ //Caso a bebida a ser removido seja o ultimo
            TpNodo* aux = (sentinela->last);

            sentinela->last = aux->next;
            (aux->next)->prev = NULL;
            sentinela->nItens--;
            free(aux);
        }
        else{ //Caso a bebida a ser removida esteja no meio da lista
            TpNodo* aux = (sentinela->last);

            while(aux != NULL){
                if((aux->bebida).code == strcmp(codigo, (aux->bebida).code)){
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

void listar(TpLista *sentinela){
    TpNodo *aux = sentinela->last;
    system("clear || cls");

    if(aux == NULL)
        printf("Nao ha Bebidas!\n");
    else{
        while(aux != NULL){
            printf("%s, %s, %d, %.2f, %d, %d \n", (aux->bebida).code, (aux->bebida).name, (aux->bebida).volume, (aux->bebida).price, (aux->bebida).qt_stock, (aux->bebida).isAlcoholic);
            aux = aux->next;
        }
    }
}

TpNodo *buscar(TpLista *sentinela){
    TpNodo *aux = sentinela->last;
    char codigo[TAM_CODE];
    system("clear || cls");

    if(aux == NULL)
        printf("Nao ha Bebidas!\n");
    else{
        printf("Informe o codigo da Bebida: ");
        scanf("%s", codigo);

        for(aux=sentinela->first; aux!=NULL; aux=aux->next) {
            if(strcmp(codigo, (aux->bebida).code) == (aux->bebida).code)
                printf("%s, %s, %d, %.2f, %d, %d \n", (aux->bebida).code, (aux->bebida).name, (aux->bebida).volume, (aux->bebida).price, (aux->bebida).qt_stock, (aux->bebida).isAlcoholic);
            else
                printf("Bebida nao cadastrada!\n");
        }
    }
    return;
}

TpNodo *comprar(TpLista *sentinela){
    TpNodo *aux = sentinela->last;
    char codigo[TAM_CODE];
    system("clear || cls");

    printf("Informe o codigo da Bebida que deseja comprar: ");
    scanf("%s", codigo);

    for(aux=sentinela->first; aux!=NULL; aux=aux->next) {
        if(strcmp(codigo, (aux->bebida).code) == (aux->bebida).code)
            (aux->bebida).qt_stock++;
    }
}

TpNodo *vender(TpLista *sentinela){
    TpNodo *aux = sentinela->last;
    char codigo, sexo;
    system("clear || cls");

    printf("Informe o codigo da Bebida que deseja vender: ");
    scanf("%s", codigo);

    for(aux=sentinela->first; aux!=NULL; aux=aux->next){
        if(strcmp(codigo, (aux->bebida).code) == (aux->bebida).code){
            if((aux->bebida).qt_stock > 0){
                printf("Voce tem mais que 18 anos? (S ou N)\n");
                scanf("%c", sexo);
                if((sexo == "S") || (sexo == "s"))
                    (aux->bebida).qt_stock--;
                else
                    printf("[ERRO]: Menor de 18 anos!\n");
            }
            else
                printf("Nao ha Bebidas!\n");
        }
    }
    return;
}

int main(){
    TpNodo *k = NULL;
    TpLista *sentinela = (TpLista*)malloc(sizeof(TpLista));
    int opcao;
    
    sentinela->nItens = 0;
    sentinela->first = NULL;
    sentinela->last = NULL;

    do{
        printf("\n\t1 - Adicionar Bebidas\n");
        printf("\t2 - Listar Bebidas\n");
        printf("\t3 - Buscar Bebidas\n");
        printf("\t4 - Excluir Bebidas\n");
        printf("\t5 - Comprar Bebidas\n");
        printf("\t6 - Vender Bebidas\n");
        printf("\t0 - Sair do Programa\n");

        printf("\tInsira a opcao que deseja: ");
        scanf("%d", &opcao);

        switch(opcao)
        {
        case 1:
            k = inserir(k, sentinela);
            break;
        case 2:
            listar(sentinela);
            break;
        case 3:
            k = buscar(sentinela);
            break;
        case 4:
            k = excluir(k, sentinela);
            break;
        case 5:
            k = comprar(sentinela);
            break;
        case 6:
            k = vender(sentinela);
            break;
        case 0:
            break;
        }
    }while(opcao != 0);

    return 0;
}
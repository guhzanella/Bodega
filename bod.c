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

int isNumeric (const char* str) 
{
    char *stop = 0;
    strtoul (str, &stop, 10); 
    return (stop - str == strlen (str));
}

TpNodo *inserir(TpNodo *k, TpLista *sentinela){
    system("clear || cls");
    int ok = 0;
    TpNodo *u = (TpNodo*)malloc(sizeof(TpNodo));

    do{
        printf("Codigo: ");
        scanf("%s", (u->bebida).code);
        printf("Bebida: ");
        scanf("%s", (u->bebida).name);
        printf("Volume (ml): ");
        scanf("%d", &(u->bebida).volume);
        if (!isNumeric ((u->bebida).volume)){
            printf("[ERRO]: Digite um valor numerico!\n\n");
            printf("Volume (ml): ");
            scanf("%d", &(u->bebida).volume);
        }else{
            (u->bebida).volume = atoi((u->bebida).volume);
            ok = 1;
        }
        printf("Preco: ");
        scanf("%f", &(u->bebida).price);
        if (!isNumeric ((u->bebida).volume)){
            printf("[ERRO]: Digite um valor numerico!\n\n");
            printf("Preco: ");
            scanf("%f", &(u->bebida).price);
        }
        printf("Quantidade: ");
        scanf("%d", &(u->bebida).qt_stock);
        printf("Alcoolica: ");
        scanf("%d", &(u->bebida).isAlcoholic);
    }while(!ok);

    system("clear || cls");

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
    printf("Bebida '%s' cadastrada(o) com sucesso!\n\n", (u->bebida).name);

    return u;
}

TpNodo *excluir(TpNodo *k, TpLista *sentinela){
    system("clear || cls");
    char codigo[TAM_CODE];

    if(sentinela->nItens != 0){
        printf("Informe o codigo da Bebida que sera removida: ");
        scanf("%s", codigo);
        printf("\n");

        if(sentinela->nItens == 1){ //Caso existe apenas uma bebida na lista
            if(strcmp((sentinela->first)->bebida.code, codigo) == 0){
                TpNodo *aux = (sentinela->first);

                sentinela->first = NULL;
                sentinela->last = NULL;
                sentinela->nItens--;
            }
            else
                printf("[ERRO]: Bebida nao cadastrada!\n\n");
        }
        else if(strcmp((sentinela->first)->bebida.code, codigo) == 0){ //Caso a bebida a ser removido seja o primeiro
            TpNodo* aux = (sentinela->first);

            sentinela->first = aux->prev;
            (aux->prev)->next = NULL;
            sentinela->nItens--;
            system("clear || cls");
            printf("A Bebida %s foi removida!\n\n", codigo);
            free(aux);
        }
        else if (strcmp((sentinela->last)->bebida.code, codigo) == 0){ //Caso a bebida a ser removido seja o ultimo
            TpNodo* aux = (sentinela->last);

            sentinela->last = aux->next;
            (aux->next)->prev = NULL;
            sentinela->nItens--;
            system("clear || cls");
            printf("A Bebida %s foi removida!\n\n", codigo);
            free(aux);
        }
        else{ //Caso a bebida a ser removida esteja no meio da lista
            TpNodo* aux = (sentinela->last);

            while(aux != NULL){
                if(strcmp((sentinela->first)->bebida.code, codigo) == 0){
                    (aux->prev)->next = aux->next;
                    (aux->next)->prev = aux->prev;
                    sentinela->nItens--;
                    system("clear || cls");
                    printf("A Bebida %s foi removida!\n", codigo);
                    free(aux);
                    break;
                }
                else
                    aux = aux->next;
            }
        }
    }
    else
        printf("[ERRO]: Nao ha Bebidas para Excluir!\n\n");

    return k;
}

void listar(TpLista *sentinela){
    system("clear || cls");
    TpNodo *aux = sentinela->last;

    if(aux == NULL)
        printf("[ERRO]: Nao ha Bebidas para Listar!\n\n");
    else{
        while(aux != NULL){
            printf("%s, %s, %d, %.2f, %d, %d \n", (aux->bebida).code, (aux->bebida).name, (aux->bebida).volume, (aux->bebida).price, (aux->bebida).qt_stock, (aux->bebida).isAlcoholic);
            aux = aux->next;
        }
        printf("\n");
    }
}

TpNodo *buscar(TpLista *sentinela){
    system("clear || cls");
    TpNodo *aux = (sentinela->last);
    char codigo[TAM_CODE];

    if(aux == NULL)
        printf("[ERRO]: Nao ha Bebidas para buscar!\n\n");
    else{
        printf("Informe o codigo da Bebida para busca-la: ");
        scanf("%s", codigo);

        for(aux=sentinela->first; aux!=NULL; aux=aux->next) {
            if(strcmp(codigo, (aux->bebida).code) == 0)
                printf("%s, %s, %d, %.2f, %d, %d \n", (aux->bebida).code, (aux->bebida).name, (aux->bebida).volume, (aux->bebida).price, (aux->bebida).qt_stock, (aux->bebida).isAlcoholic);
            else
                printf("[ERRO]: Bebida nao cadastrada! Nao foi possivel realizar a Busca!\n\n");

            printf("\n");    
        }
    }

    return;
}

TpNodo *comprar(TpLista *sentinela){
    system("clear || cls");
    TpNodo *aux = sentinela->last;
    char codigo[TAM_CODE];
    int qtd;

    for(aux=sentinela->first; aux!=NULL; aux=aux->next) {
        printf("Informe o codigo da Bebida que deseja comprar: ");
        scanf("%s", codigo);

        if(strcmp(codigo, (aux->bebida).code) == 0){
            printf("Informe a quantidade: ");
            scanf("%d", &qtd);
            (aux->bebida).qt_stock += qtd;
            printf("\n Compra realizada! +%d unidade(s) comprada(s) da Bebida '%s'\n", qtd, (aux->bebida).name);
            printf("Estoque atual da Bebida '%s': %d\n\n", (aux->bebida).name, (aux->bebida).qt_stock);
        }
    }
    
    return;
}

TpNodo *vender(TpLista *sentinela){
    system("clear || cls");
    TpNodo *aux = sentinela->last;
    char codigo[TAM_CODE];
    int idade;

    if(aux == NULL)
        printf("[ERRO]: Nao ha Bebidas para vender!\n\n");
    else{
        for(aux=sentinela->first; aux!=NULL; aux=aux->next){
            printf("Informe o codigo da Bebida que deseja vender: ");
            scanf("%s", codigo);

            if(strcmp(codigo, (aux->bebida).code) == 0){
                if((aux->bebida).qt_stock > 0){
                    printf("Digite a idade: ");
                    scanf("%d", &idade);
                    if((idade < 18) && (aux->bebida).isAlcoholic == 1)
                        printf("[ERRO]: Menor de 18 anos nao eh permitido beber alcool!\n\n");
                    else{
                        (aux->bebida).qt_stock--;
                        printf("1 unidade vendida da Bebida '%s'!\n", (aux->bebida).name);
                        printf("Estoque atual da Bebida '%s': %d\n\n", (aux->bebida).name, (aux->bebida).qt_stock);
                    }
                }
                else
                    printf("[ERRO]: Estoque da Bebida %s esta zerado!\n\n", (aux->bebida).name);
            }
            else
                printf("[ERRO]: Bebida nao encontrada para Venda!\n\n");
        }
    }

    return;
}

int main(){
    system("clear || cls");
    TpNodo *k = NULL;
    TpLista *sentinela = (TpLista*)malloc(sizeof(TpLista));
    int opcao;
    
    sentinela->nItens = 0;
    sentinela->first = NULL;
    sentinela->last = NULL;

    do{
        printf("\t1 - Adicionar Bebidas\n");
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
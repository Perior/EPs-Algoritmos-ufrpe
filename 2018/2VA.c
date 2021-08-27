#include <stdio.h>
#include <stdlib.h>

void removeEntreListas(celula *lista1, celula *lista2) {
   celula *p, *q;
   celula *r, *s;

   p = lista1;
   q = lista1->prox;

   r = lista2;
   s = lista2->prox;

   while(q != NULL){
        while (q->conteudo != s->conteudo) {
          p = q;
          q = q->prox;
       }
       if (q != NULL) {
          p->prox = q->prox;
          free (q);
       }
   }

   busca_e_removeEntreListas(celula *lista1, celula *s);
}

//Insere um elemento na frente da lista
void insereFrente(int n){
    // Checa se deque está vazio ou não
    if(estaCheio()){
        return;
    }

    //Se a fila está inicialmente vazia:
    if(frente == -1){
        frente = 0;
        tras = 0;
    }
    //Frente está na primeira posição da fila(tamanho é um int da struct deque):
    else if (frente == 0){
        frente = tamanho - 1;
    }
    //Decrementa frente
    else{
        frente--;
    }

    //Insere o elemento no deque
    v[frente] = n;
}

//Insere elemento na parte de trás da lista
void insereTras(int n){
    // Checa se deque está vazio ou não
    if(estaCheio()){
        return;
    }

    //Se a lista está inicialmente vazia:
    if(frente == -1){
        frente = 0;
        tras = 0;
    }
    //Se trás está na última posição da lista:
    else if (tras == tamanho-1){
        tras = 0;
    }
    //Incrementa o fim de trás
    else{
        tras++;
    }

    //Insere o elemento n no deque
    v[tras] = n;
}

//Remove elemento da frente do deque
void deletaFrente(){
    // Checa se deque está vazio ou não
    if(estaCheio()){
        return;
    }

    //Se o deque possui apenas um elemento:
    if (frente == tras){
        frente = -1;
        tras = -1;
    }
    else{
        //Volta pra posição inicial
        if (frente == tamanho -1){
            frente = 0;
        }
        //Incrementa frente para remover seu valor atual
        else{
            frente++;
        }
    }
}

// Deleta o elemento por trás
void deletaTras(){
    // Checa se deque está vazio ou não
    if(estaCheio()){
        return;
    }

    //Se deque possui apenas um elemento:
    if (frente == tras){
        frente = -1;
        tras = -1;
    }
    else if (tras == 0){
        tras = tamanho-1;
    }
    else{
        tras--;
    }
}

void imprimeFolhas (arvore a){
   if (a != NULL) {
      imprimeFolhas(a->esquerda);
      printf ("%d\n", a->conteudo);
      imprimeFolhas(a->direita);
   }
}

void TTT(int x[], int n){
    int i = 0;
    int j;

    for(j=0; j<n; j++){
        if(x[j]>0){
            x[i] += x[j];
            i++;
        }
        else{
            x[i] = x[j];
            i++;
        }
    }
    return i;
}


int alturaEsquerda(arvore r){
    if(r == NULL){
        return -1;
    }
    else{
        int he = altura(r->esquerda);
        return he+1;
    }
}

int alturaDireita(arvore r){
    if(r == NULL){
        return -1;
    }
    else{
        int hd = altura(r->direita);
        return hd+1;
    }
}

void arvoreAVL(arvore r){
    if(r == NULL){
        return true;
    }

    int he = alturaEsquerda(r);
    int hd = alturaDireita(r);
    //Propriedade que todos os nós devem respeitar para que ela seja AVL
    if((he - hd) <= 1){
        arvoreAVL(r->direita);
        arvoreAVL(r->esquerda);
        return true;
    }
    else{
        return false;
    }
}

arvore* binaryToSorted (int v[], int e, int d) {
    if(e > d){
        return NULL;
    }

    int m = (e+d)/2;
    arvore *raiz = (arvore*)malloc(sizeof(arvore));
    raiz->chave = v[m];


    raiz->esquerda = ordEmAVL(v, e, m-1);

    raiz->direita = ordEmAVL(v, m+1, d);

    return raiz;
}

int acharMax(arvore r){
    if(r == NULL){
        return INT_MIN;
    }

    int centro = r->conteudo;
    int lesqu = acharMax(r->esquerda);
    int ldir = acharMax(r->direita);

    if(lesqu > centro){
        centro = lesqu;
    }
    if(ldir > centro){
        centro = ldir;
    }

    return centro;
}

int acharMin(arvore r){
    if(r == NULL){
        return INT_MAX;
    }

    int centro = r->conteudo;
    int lesqu = acharMin(r->esquerda);
    int ldir = acharMin(r->direita);

    if(lesqu < centro){
        centro = lesqu;
    }
    if(ldir < centro){
        centro = ldir;
    }

    return centro;
}

//Exerc�cio Programa 1 (An�lise Emp�rica de Algoritmos Recursivos)
//Data: 22/10/2017
//Algoritmos e Estruturas de Dados


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_PASSO 700
#define TAM_MAX 21000

//Essa vari�vel vai contar o n�mero de opera��es feitas nas fun��es de busca do maior elemento.
int quantidade_operacoes;

//Fun��o utilizada para preencher os elementos do vetor.
//A fun��o 'rand' est� suprindo os elementos com valores aleat�rios.
void preencheVetor(int n, int v[]){
    int i;
    for(i=0; i<=n; i++){
        v[i] = rand();
    }
}


int separador(int v[], int e, int d){
    int pivo = v[e];
    int leftCont = e+1;
    int rightCont = d;
    int aux;

    while(leftCont <= rightCont){
        if(v[leftCont] <= pivo){
            leftCont++;
        }
        else if(pivo < v[rightCont]){
            rightCont--;
        }
        else{
            aux = v[leftCont];
            v[leftCont] = v[rightCont];
            v[rightCont] = aux;
            leftCont++;
            rightCont--;
        }

    }
    v[e] = v[rightCont];
    v[rightCont] = pivo;

    //No fim do while, rightCont ser� a posi��o do vetor 'pivo' e leftCont = j+1.
    return rightCont;
}


void crescRec(int v[], int e, int d){
    int m;

    if(e < d){
        m = separador(v, e, d);

        crescRec(v, e, m-1);
        crescRec(v, m+1, d);
    }
}

int buscaRec(int x, int e, int d, int v[]){
    int m;
    quantidade_operacoes++;
    if(d-e == 1){
        return d;
    }
    else{
        m = (d+e)/2;

        if(v[m] < x){
            buscaRec(x, m, d, v);
        }
        else{
            buscaRec(x, e, m, v);
        }
    }

}

int buscaRec2(int n, int v[], int x){
    return buscaRec(x, -1, n, v);
}


int buscaIt(int v[], int x){
    int j = 0;

    while(v[j] < x && j < TAM_MAX){
        quantidade_operacoes++;
        j++;
    }
    return j;
}


//As duas pr�ximas fun��es geram e arquivam as inst�ncias e a quantidade de opera��es de cada tipo de algoritmo.
//Primeira Recursiva e segunda Iterativa.
void instanciasRec(int n, int x){

    FILE *arquivo = fopen("buscaRec.txt", "w");

    for(n=TAM_PASSO; n<=TAM_MAX; n+=TAM_PASSO){
        quantidade_operacoes = 0;
        int v[n];

        preencheVetor(n, v);
        crescRec(v, 0, n-1);

        x = v[rand()%n];

        buscaRec2(n-1, v, x);

        fprintf(arquivo, "%d\t%d\n", n, quantidade_operacoes);
    }
    fclose(arquivo);
}

void instanciasIt(int n, int x){

    FILE *arquivo = fopen("buscaIt.txt", "w");

    for(n=TAM_PASSO; n<=TAM_MAX; n+=TAM_PASSO){
        quantidade_operacoes = 0;
        int v[n];

        preencheVetor(n, v);
        crescRec(v, 0, n-1);

        x = v[rand()%n];

        buscaIt(v, x);

        fprintf(arquivo, "%d\t%d\n", n, quantidade_operacoes);
    }
    fclose(arquivo);
}


int main()
{
    srand(time(NULL));
    int n = TAM_MAX;
    int v[n];
    int x;

    instanciasRec(n, x);
    instanciasIt(n, x);

    preencheVetor(n, v);
    crescRec(v, 0, n-1);

    x = v[rand()%n];

    printf("Indice 'j' da posicao do elemento %d no vetor: %d\n\n", x, buscaRec2(n, v, x));

    x = v[rand()%n];

    printf("Indice 'j' da posicao do elemento %d no vetor: %d\n\n", x, buscaIt(v, x));

    return 0;
}


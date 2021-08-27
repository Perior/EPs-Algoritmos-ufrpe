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
        v[i] = (int)(((float)rand() / (float)RAND_MAX) * ((float)RAND_MAX * 2) - RAND_MAX);
    }
}

int max(int v1, int v2){
    if(v1 > v2){
        return v1;
    }
    else{
        return v2;
    }
}

int max3(int v1, int v2, int v3){
    if(v1 > v2 && v1 > v3){
        return v1;
    }
    else if(v2 > v3){
        return v2;
    }
    else{
        return v3;
    }
}


int somaMaxRec(int v[], int e, int d){
    int m, i, soma;
    int maxEsquerda, maxDireita;
    int max2Esquerda, max2Direita, maxSoma;

    quantidade_operacoes++;

    if(e==d){
        return max(0, v[d]);
    }

    m = (d+e)/2;

    maxEsquerda = somaMaxRec(v, e, m);
    maxDireita = somaMaxRec(v, m+1, d);

    max2Esquerda = v[m];
    soma = v[m];

    for(i=m-1; i>=e; i--){
        soma += v[i];
        max2Esquerda = max(max2Esquerda, soma);
    }

    max2Direita = v[m+1];
    soma = v[m+1];

    for(i=m+2; i<d; i++){
        soma += v[i];
        max2Direita = max(max2Direita, soma);
    }

    maxSoma = max2Esquerda + max2Direita;

    return max3(maxEsquerda, maxDireita, maxSoma);
}

int somaMaxIt(int v[], int n){
    int i;
    int maxSoma = 0;
    int soma = 0;

    for(i=0; i<n; i++){
        quantidade_operacoes++;

        if(v[i] + soma < 0){
            soma = 0;
        }
        else{
            soma += v[i];
        }

        if(soma > maxSoma){
            maxSoma = soma;
        }
    }

    return maxSoma;
}

//As duas pr�ximas fun��es geram e arquivam as inst�ncias e a quantidade de opera��es de cada tipo de algoritmo.
//Primeira Recursiva e segunda Iterativa.

void instanciasRec(int n){
    int x;

    FILE *arquivo = fopen("somaMaxRec.txt", "w");

    for(n=TAM_PASSO; n<=TAM_MAX; n+=TAM_PASSO){
        quantidade_operacoes = 0;
        int v[n];

        preencheVetor(n, v);

        x = somaMaxRec(v, 0, n-1);

        fprintf(arquivo, "%d\t%d\n", n, quantidade_operacoes);
    }
    fclose(arquivo);
}

void instanciasIt(int n){
    int x;

    FILE *arquivo = fopen("somaMaxIt.txt", "w");

    for(n=TAM_PASSO; n<=TAM_MAX; n+=TAM_PASSO){
        quantidade_operacoes = 0;
        int v[n];

        preencheVetor(n, v);

        x = somaMaxIt(v, n);

        fprintf(arquivo, "%d\t%d\n", n, quantidade_operacoes);
    }
    fclose(arquivo);
}


int main()
{
    srand(time(NULL));
    int n = TAM_MAX;
    int v[n];
    int i;

    instanciasRec(n);
    instanciasIt(n);

    preencheVetor(n, v);

    printf("\nSegmento de soma maxima do vetor (Recursivo): %d", somaMaxRec(v, 0, n-1));

  //preencheVetor(n, v);

    printf("\n\nSegmento de soma maxima do vetor (Iterativo): %d", somaMaxIt(v, n));

    return 0;
}

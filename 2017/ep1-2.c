//Exerc�cio Programa 1 (An�lise Emp�rica de Algoritmos Recursivos)
//Data: 22/10/2017
//Algoritmos e Estruturas de Dados


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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
    quantidade_operacoes++;
    if(e < d){
        m = separador(v, e, d);

        crescRec(v, e, m-1);
        crescRec(v, m+1, d);
    }
}

void crescIt(int v[], int n){
    int i, j;
    int aux;
    for(i=0; i<n; i++){
        for(j=0; j<n-i; j++){
            quantidade_operacoes++;
            if(v[j] > v[j+1]){
                aux = v[j];
                v[j] = v[j+1];
                v[j+1] = aux;
            }
        }
    }
}

bool checagem(int v[], int n, int ver){
    int i, aux=0;

    for(i=0; i<n; i++){
        if(v[i] <= v[i+1]){
            continue;
        }
        else{
            break;
        }
    }
    if(!ver){
        if(i == n-1){
            return true;
        }
        else{
            return false;
        }

    }
    else{
        if(i == n){
            return true;
        }
        else{
            return false;
        }
    }
}


//As duas pr�ximas fun��es geram e arquivam as inst�ncias e a quantidade de opera��es de cada tipo de algoritmo.
//Primeira Recursiva e segunda Iterativa.

void instanciasRec(int n){

    FILE *arquivo = fopen("crescRec.txt", "w");

    for(n=TAM_PASSO; n<=TAM_MAX; n+=TAM_PASSO){
        quantidade_operacoes = 0;
        int v[n];

        preencheVetor(n, v);

        crescRec(v, 0, n-1);

        fprintf(arquivo, "%d\t%d\n", n, quantidade_operacoes);
    }
    fclose(arquivo);
}

void instanciasIt(int n){

    FILE *arquivo = fopen("crescIt.txt", "w");

    for(n=TAM_PASSO; n<=TAM_MAX; n+=TAM_PASSO){
        quantidade_operacoes = 0;
        int v[n];

        preencheVetor(n, v);
        crescIt(v, n);

        fprintf(arquivo, "%d\t%d\n", n, quantidade_operacoes);
    }
    fclose(arquivo);
}

//Fun��o main b�sica. Imprime para o usu�rio os valores m�ximos do vetor no caso Recursivo e Iterativo
//O valor impresso ser� o mesmo nos dois casos, o valor m�ximo � um s�.
//Mas, para fins de teste, basta retirarmos o coment�rio da fun��o preencheVetor(); para gerarmos novos valores.
// (Se necess�rio, diminuir os valores definidos 'TAM_MAX' e 'TAM_PASSO' e dar uma margem ao 'rand' na fun��o gerarVetor(); Ex: rand()%100).
int main()
{
    srand(time(NULL));

    int n = TAM_MAX;
    int v[n];

    printf("Aguarde um momento. Processando...");

    instanciasRec(n);
    instanciasIt(n);

    preencheVetor(n, v);

    crescRec(v, 0, n-1);
    if(checagem(v, n, 0)){
        printf("\n\nO vetor foi ordenado com sucesso!\n");
    }
    else{
        printf("Erro ao ordenar vetor!\n");
    }

    preencheVetor(n, v);

    crescIt(v, n);
    if(checagem(v, n, 1)){
        printf("O vetor foi ordenado com sucesso!\n");
    }
    else{
        printf("Erro ao ordenar vetor!\n");
    }

    return 0;
}

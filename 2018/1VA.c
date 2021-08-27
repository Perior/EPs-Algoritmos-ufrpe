//Exerc�cio Programa 1 (An�lise Emp�rica de Algoritmos Recursivos)
//Data: 08/05/2018
//Algoritmos e Estruturas de Dados


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define TAM_PASSO 700
#define TAM_MAX 21000


//Fun��o utilizada para preencher os elementos do vetor.
//A fun��o 'rand' est� suprindo os elementos com valores aleat�rios.
void preencheVetor(int n, int v[]){
    int i;
    for(i=0; i<=n; i++){
        v[i] = rand();
    }
}

//Fun��o que compara dois elementos e retorna o maior.
int max(int v1, int v2){
    if(v1 > v2){
        return v1;
    }
    else{
        return v2;
    }
}

//Fun��o que compara tr�s elementos e retorna o maior.
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

//Fun��o que checa se o vetor est� em ordem crescente.
//A vari�vel 'ver' est� aqui para definir que fun��o (0 - Recursiva ou 1 - Iterativa) ir� ser checada.
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


//Bibliografia: https://www.ime.usp.br/~pf/algoritmos/aulas/footnotes/crescente.html
//Usando um valor como pivot, esta fun��o ir� checar se os elementos s�o maiores ou menores que este pivot.
//'leftCount' ir� checar da esquerda pra direita e 'rightCount' da direita para a esquerda no vetor.
//Se 'leftCount' for um valor maior que meu pivot e 'rightCount' for um elemento menor, eles ir�o trocar de lugar.
//No fim, meu pivot ir� assumir a posi��o do meio, tendo elementos menores que ele a sua esquerda e os maiores a sua direita.
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

    //No fim do while, rightCont ser� a posi��o do meio do vetor e leftCont = j+1.
    return rightCont;
}

//Fun��o recursiva que repete o processo de separa��o dos dois lados do vetor, tendo como centro 'm'.
void crescRec(int v[], int e, int d){
    int m;
    //quantidade_operacoes++;
    if(e < d){
        m = separador(v, e, d);

        crescRec(v, e, m-1);
        crescRec(v, m+1, d);
    }
}

//Bibliografia: https://www.ime.usp.br/~pf/analise_de_algoritmos/aulas/binarysearch.html
//Fun��o de Busca num vetor em ordem crescente.
//Retornamos 'd' caso o vetor s� tenha 1 elemento.
//Se 'x' for maior que o elemento no centro do vetor ent�o repetiremos o processo no lado direito do vetor
//Caso 'x' seja menor que o centro, faremos no lado esquerdo.
int locRec(int x, int e, int d, int v[]){
    int m;
    //quantidade_operacoes++;
    if(d-e == 1){
        return d;
    }
    else{
        m = (d+e)/2;

        if(v[m] < x){
            locRec(x, m, d, v);
        }
        else{
            locRec(x, e, m, v);
        }
    }

}
//Bibliografia: https://www.ime.usp.br/~pf/algoritmos/aulas/bubi.html
//Fun��o de inser��o de par�metros.
//Retorna o �ndice do elemento que buscamos.
int locRec2(int n, int v[], int x){
    return locRec(x, -1, n, v);
}


void somaBusca(int v[], int t){

}

//Fun��o principal com os testes b�sicos de cada fun��o.
//Se necess�rio, alterar os valores definidos TAM_MAX e TAM_PASSO e/ou o 'rand' na fun��o preencheVetor.
int main()
{
    srand(time(NULL));

    int n = TAM_MAX;
    int v[n];
    int x;

    preencheVetor(n, v);

    crescRec(v, 0, n-1);
    x = v[rand()%n];

    //Recursivos:
    printf("Testes das funcoes Recursivas: ");

    //Ordena��o Crescente:
    if(checagem(v, n, 0)){
        printf("\tO vetor foi ordenado com sucesso!\n");
    }
    else{
        printf("\tErro ao ordenar vetor!\n");
    }



    return 0;
}

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


//Todos os algoritmos deste c�digo foram estudados e baseados nos do site https://www.ime.usp.br/~pf/algoritmos/
//As vari�veis 'd' e 'e' representam, respectivamente, os lados direito e esquerdo dos arrays.
//Os "lados" s�o geralmente gerados por uma vari�vel 'm' que representa o meio, a metade do array original v[e,...,d]
//A partir da� teremos dois vetores. Um com tamanho v[e,...,m] (vE) e outro de tamanho v[m+1,...,d] (vD).



//Os algoritmos maxRec e maxIt tamb�m foram baseados em: http://www.decom.ufop.br/toffolo/site_media/uploads/2011-1/bcc402/slides/08._divisao_e_conquista.pdf
//Fun��o recursiva do tipo divis�o-e-conquista que retorna o maior elemento de um array.
//Note que quando n for 1 s� haver� um elemento no array e, portanto, ele ser� o maior. (d - e) resultam no tamanho do meu vetor, ou seja, n.
//A fun��o retorna o maior elemento entre os lados direito/esquerdo.
int maxRec(int v[], int e, int d){
    //quantidade_operacoes++;
    if(d - e <= 1){
        return max(v[e], v[d]);
    }
    else{
        int m;

        m = (d+e)/2;

        int vE = maxRec(v, e, m);
        int vD = maxRec(v, m+1, d);

        return max(vE, vD);
    }
}

//Fun��o Iterativa para encontrar o valor m�ximo do vetor.
//Minha v�riavel auxiliar (aux) ir� receber meu vetor inicial e ir� ser comparada com os outros valores at� chegarmos no �ltimo valor n-1.
//Aux vai receber um valor maior toda vez que este for encontrado. Esse valor � retornado.
int maxIt(int n, int v[]){
    int aux;
    int i;
    aux = v[0];

    for(i=1; i<n; i++){
        //quantidade_operacoes++;
        if(aux < v[i]){
            aux = v[i];
        }
    }
    return aux;
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

//Fun��o iterativa de organiza��o de vetores.
//Usando uma vari�vel auxiliar 'aux', toda vez que meu elemento for maior que seu sucessor inverto suas posi��es. BubbleSort.
void crescIt(int v[], int n){
    int i, j;
    int aux;
    for(i=0; i<n; i++){
        for(j=0; j<n-i; j++){
            //quantidade_operacoes++;
            if(v[j] > v[j+1]){
                aux = v[j];
                v[j] = v[j+1];
                v[j+1] = aux;
            }
        }
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

//Fun��o iterativa de busca em um vetor ordenado crescentemente.
//'j' ser� implementado at� que achemos um valor v[j] igual ou maior que 'x'
//'j' ser� menor que TAM_MAX.
//Retorna o �ndice 'j' do elemento que buscamos.
int locIt(int v[], int x){
    int j = 0;

    while(v[j] < x && j < TAM_MAX){
        //quantidade_operacoes++;
        j++;
    }
    return j;
}

//Bibliografia: https://www.ime.usp.br/~cris/aulas/11_1_338/slides/aula5.pdf
//Fun��o Recursiva para obten��o do segmento de soma m�xima de um vetor.
//Retornamos o maior valor entre 0, v[d] caso o vetor tenha tamanho 1.
//Dividindo o vetor no meio ('m'), teremos dois lados do vetor 'e' e 'd'.
int segRec(int v[], int e, int d){
    int m, i, soma;
    int maxEsquerda, maxDireita;
    int max2Esquerda, max2Direita, maxSoma;

    //quantidade_operacoes++;

    if(e==d){
        return max(0, v[d]);
    }

    m = (d+e)/2;
    //Essas vari�veis armazenam os valores da busca em seus respectivos lados.
    maxEsquerda = segRec(v, e, m);
    maxDireita = segRec(v, m+1, d);

    max2Esquerda = v[m];
    soma = v[m];
    //Aqui somamos os elementos de 'm-1' (primeiro elemento menor que o meio) at� o primeiro elemento 'e' (lado esquerdo).
    //'max2Esquerda' recebe a soma dos elementos ou o elemento do centro, dependendo do maior.
    for(i=m-1; i>=e; i--){
        soma += v[i];
        max2Esquerda = max(max2Esquerda, soma);
    }

    max2Direita = v[m+1];
    soma = v[m+1];
    //Mesmo caso aqui, somamos v[m+1] com os elementos de 'm+2' (segundo elemento maior que o centro)
    //at� o �ltimo elemento 'd' (lado direito).
    //'max2Direita' recebe a soma dos elementos ou o primeiro elemento maior que o meio(v[m+1]), dependendo do maior.
    for(i=m+2; i<d; i++){
        soma += v[i];
        max2Direita = max(max2Direita, soma);
    }
    //'maxSoma' vai receber a soma dos maiores valores anteriores.
    maxSoma = max2Esquerda + max2Direita;

    //Retorna-se o maior valor entre os tr�s.
    return max3(maxEsquerda, maxDireita, maxSoma);
}

//Fun��o Iterativa que retorna a maior soma de um segmento de um vetor.
//Soma-se a vari�vel 'soma' e o elemento do vetor v[] quando estes geram um n�mero positivo. Caso gerem um negativo 'soma' recebe 0.
//Se ele for maior que 'maxSoma', 'maxSoma' ir� receber este n�mero.
//O algoritmo faz isso para cada valor do vetor sucessivamente.
//No fim teremos nossa soma m�xima armazenada na vari�vel 'maxSoma'.
int segIt(int v[], int n){
    int i;
    int maxSoma = 0;
    int soma = 0;

    for(i=0; i<n; i++){
        //quantidade_operacoes++;

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
//Fun��o auxiliar que encontra o node com valor minimo.
Node* encontraMin(Node* raiz){
    while(raiz->left){
        raiz = raiz->left;
    }

    return raiz;
}
//Fun��o recursiva para encontrar o sucessor de uma chave k.
//Notar que o sucessor 'suc' � passado como referencia.
//Na fun��o main se o node 'suc' for igual a NULL, devolver -1(k � o maior).
//Se n�o, 'suc' ter� o valor do sucessor de 'k'
void encontraSuc(Node* raiz, Node*& suc, int k){
    if(raiz == NULL){
        return;
    }
    //Se um node com o valor k � encontrado,
    //o valor minimo da subarvore direita � o sucessor.
    if(raiz->aux == k){
        if(raiz->right){
            suc = encontraMin(raiz->right);
        }
    }
    //Se menor, fazer para o lado esquerdo.
    else if(k < raiz->aux){
        suc = raiz;
        encontraSuc(raiz->left, suc, k);
    }
    //Se maior, fazer para o lado direito.
    else{
        encontraSuc(raiz->right, suc, k);
    }
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

    //Maior Elemento:
    printf("\n\n\tMaior elemento do Vetor (Recursividade): %d\n", maxRec(v, 0, n-1));

    //Ordena��o Crescente:
    if(checagem(v, n, 0)){
        printf("\tO vetor foi ordenado com sucesso!\n");
    }
    else{
        printf("\tErro ao ordenar vetor!\n");
    }

    //Busca no Vetor Crescente:
    printf("\tIndice 'j' da posicao do elemento %d no vetor: %d\n", x, locRec2(n, v, x));

    //Soma M�xima:
    printf("\tSegmento de soma maxima do vetor (Recursivo): %d\n", segRec(v, 0, n-1));

    preencheVetor(n, v);

    crescIt(v, n);
    x = v[rand()%n];

    //Iterativos:
    printf("\nTeste das funcoes Iterativas: ");

    //Maior Elemento:
    printf("\n\n\tMaior elemento do Vetor (Iterativo): %d\n", maxIt(n, v));

    //Ordena��o Crescente:
    if(checagem(v, n, 1)){
        printf("\tO vetor foi ordenado com sucesso!\n");
    }
    else{
        printf("\tErro ao ordenar vetor!\n");
    }

    //Busca no Vetor Crescente:
    printf("\tIndice 'j' da posicao do elemento %d no vetor: %d\n", x, locIt(v, x));

    //Soma M�xima:
    printf("\tSegmento de soma maxima do vetor (Iterativo): %d\n\n", segIt(v, n));

    return 0;
}

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

//Fun��o que compara dois elementos e retorna o maior.
int max(int v1, int v2){
    if(v1 > v2){
        return v1;
    }
    else{
        return v2;
    }
}
//Ambos os algoritmos a seguir foram baseados em partes nos algoritmos do nosso "guru" Paulo Feofiloff
//E tamb�m do site: http://www.decom.ufop.br/toffolo/site_media/uploads/2011-1/bcc402/slides/08._divisao_e_conquista.pdf

//Fun��o recursiva do tipo divis�o-e-conquista que retorna o maior elemento de um array.
//Note que quando n for 1 s� haver� um elemento no array e, portanto, ele ser� o maior. (d - e) resultam no tamanho do meu vetor, ou seja, n.
//A v�riavel 'm' ir� receber a metade do meu vetor.
//'d' e 'e' passam a ser, respectivamente, os lados direito e esquerdo do array.
//A partir da� teremos dois vetores. Um com tamanho v[e,...,m] (vE) e outro de tamanho v[m+1,...,d] (vD).
//Fazemos a divis�o de cada novamente, at� o caso base e retornamos o maior dos dois vetores vE ou vD.

int maxRec(int v[], int e, int d){
    quantidade_operacoes++;
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
        quantidade_operacoes++;
        if(aux < v[i]){
            aux = v[i];
        }
    }
    return aux;
}

//As duas pr�ximas fun��es geram e arquivam as inst�ncias e a quantidade de opera��es de cada tipo de algoritmo.
//Primeira Recursiva e segunda Iterativa.
void instanciasRec(int n){

    FILE *arquivo = fopen("instanciasRec.txt", "w");

    for(n=TAM_PASSO; n<=TAM_MAX; n+=TAM_PASSO){
        quantidade_operacoes = 0;
        int v[n];

        preencheVetor(n, v);
        maxRec(v, 0, n-1);

        fprintf(arquivo, "%d\t%d\n", n, quantidade_operacoes);
    }
    fclose(arquivo);
}

void instanciasIt(int n){

    FILE *arquivo = fopen("instanciasIt.txt", "w");

    for(n=TAM_PASSO; n<=TAM_MAX; n+=TAM_PASSO){
        quantidade_operacoes = 0;
        int v[n];

        preencheVetor(n, v);
        maxIt(n, v);

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
    instanciasRec(n);
    instanciasIt(n);

    preencheVetor(n, v);

    printf("Maior elemento do Vetor (Recursividade): %d\n", maxRec(v, 0, n-1));

    // preencheVetor(n, v);

    printf("Maior elemento do Vetor (Iterativo): %d\n", maxIt(n, v));

    return 0;
}

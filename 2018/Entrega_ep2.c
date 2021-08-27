//Exerc�cio Programa 2 (An�lise Emp�rica de Algoritmos Recursivos)
//Data: 19/06/2018
//Algoritmos e Estruturas de Dados


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Struct que gere um tipo Pontos, que possui duas vari�veis x,y que s�o as coordenadas lidas do arquivo.
typedef struct Pontos{
    int x;
    int y;
}Pontos;

//Fun��o que compara dois elementos e retorna o menor.
double menor2(double v1, double v2){
    if(v1 < v2){
        return v1;
    }
    else{
        return v2;
    }
}

//Fun��o que compara tr�s elementos e retorna o menor.
double menor3(double v1, double v2, double v3){
    if(v1 < v2 && v1 < v3){
        return v1;
    }
    else if(v2 < v3){
        return v2;
    }
    else{
        return v3;
    }
}

//Bibliografia: https://www.ime.usp.br/~pf/algoritmos/aulas/footnotes/crescente.html
//Usando um valor como pivot, esta fun��o ir� checar se os elementos s�o maiores ou menores que este pivot.
//'leftCount' ir� checar da esquerda pra direita e 'rightCount' da direita para a esquerda no vetor.
//Se 'leftCount' for um valor maior que meu pivot e 'rightCount' for um elemento menor, eles ir�o trocar de lugar.
//No fim, meu pivot ir� assumir a posi��o do meio, tendo elementos menores que ele a sua esquerda e os maiores a sua direita.
int separador(Pontos v[], int e, int d){
    Pontos pivo = v[e];
    int leftCont = e+1;
    int rightCont = d;
    Pontos aux;

    while(leftCont <= rightCont){
        if(v[leftCont].x <= pivo.x){
            leftCont++;
        }
        else if(pivo.x < v[rightCont].x){
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
void crescRec(Pontos v[], int e, int d){
    int m;
    if(e < d){
        m = separador(v, e, d);

        crescRec(v, e, m-1);
        crescRec(v, m+1, d);
    }
}

//Calcula a dist�ncia euclidiana entre dois pontos;
double calculoDistancia(Pontos coords[], int i, int j){
    double dx = pow((coords[i].x - coords[j].x), 2);
    double dy = pow((coords[i].y - coords[j].y), 2);
    double euclid = sqrt(dx+dy);

    return euclid;
}

//Usei como base o algoritmo de soma m�xima.
//Bibliografia: https://www.ime.usp.br/~cris/aulas/11_1_338/slides/aula5.pdf
//O algoritmo checa os subpares gerados e retorna a menor distancia euclidiana entre dois pontos.
//Dividindo o vetor no meio ('m'), teremos dois lados do vetor 'e' e 'd'.
double recDivis(Pontos coords[], int e, int d){
    int m, i;
    double minEsquerda, minDireita;
    double euclid;
    double min2Esquerda, min2Direita, minEuclid;

    crescRec(coords, e, d-1);

    if(d <= e+2){
        return calculoDistancia(coords, d, e);
    }

    m = (d+e)/2;

    //Essas vari�veis armazenam os valores da busca em seus respectivos lados.
    minEsquerda = recDivis(coords, e, m+1);
    minDireita = recDivis(coords, m, d);

    min2Esquerda = calculoDistancia(coords, m-1, m);
    euclid = calculoDistancia(coords, m-1, m);

    //euclid recebe o menor valor entre ela mesma ou a dist�ncia entre os valores de 'm-1' at� 'e'.
    //'min2Esquerda' recebe o menor elemento entre ela mesma e os valores de 'euclid' que variam.
    for(i=e; i<m; i++){
        euclid = menor2(euclid, calculoDistancia(coords, i, i-1));
        min2Esquerda = menor2(min2Esquerda, euclid);
    }


    min2Direita = calculoDistancia(coords, m, m+1);
    euclid = calculoDistancia(coords, m, m+1);

    //Mesmo caso aqui, a diferen�a � o lado do vetor que estamos comparando [m+1...d].
    for(i=m+1; i<d; i++){
        euclid = menor2(euclid, calculoDistancia(coords, i, i+1));
        min2Direita = menor2(min2Direita, euclid);
    }
    //V�riavel recebe a menor distancia entre os calculos anteriores.
    minEuclid = menor2(min2Direita, min2Esquerda);

    return menor3(minEsquerda, minDireita, minEuclid);
}

//Essa fun��o faz o c�lculo da dist�ncia em todos os pontos e compara com o resultado da fun��o recursiva.
//Assim vamos ter as inst�ncias (o valor do vetor ordenado em que os pontos est�o).
void pegaInstancias(Pontos coords[], double menorDist, int tamMax){
    int i, j;

    for(i=0; i<tamMax; i++){
        for(j=0; j<tamMax; j++){
            if(j != i){
                if(menorDist == calculoDistancia(coords, i, j)){
                    printf("\nInstancia dos Pontos (No vetor ordenado): |%d == %d|\n", i, j);
                    return;
                }
            }
        }
    }
}

//Fun��o de leitura de arquivo.
void readFile(){
    int linha = 1;
    int pegaLinhaX = 2;
    int pegaLinhaY = 3;

    FILE* arquivo = fopen("trembala.dat", "r");

    if(arquivo == NULL){
        printf("\nNao foi possivel abrir o arquivo!\n\n");
        return;
    }

    //Pegamos o primeiro n�mero j� que este define o tamanho da quantidade de elementos do meu vetor.
    //Voltamos o ponteiro para o come�o do arquivo para evitar malfuncionamentos.
    int tamanhoVetor;
    fscanf(arquivo, "%d%*c", &tamanhoVetor);
    fseek(arquivo, 0, SEEK_SET);

    Pontos coords[tamanhoVetor];
    //O indice 'i' ir� determinar a posi��o em que vou armazenar meus elementos no vetor.
    int i = 0;

    //Enquanto n�o atingirmos o fim do arquivo, se o ponteiro estiver na segunda linha (x)
    //o c�digo ir� armazenar (fscanf) inteiros no vetor coordenadas X.
    while(!feof(arquivo)){
        if(linha == pegaLinhaX){
            fscanf(arquivo, "%d", &coords[i].x);
            i++;
        }
        //Mesmo c�digo, por�m para a linha 3 (y)
        if(linha == pegaLinhaY){
            fscanf(arquivo, "%d", &coords[i].y);
            i++;
        }
        if(fgetc(arquivo) == '\n'){
            linha++;
            i = 0;
        }
    }
    fclose(arquivo);

    //Chamada da fun��o.
    double menorDist = recDivis(coords, 0, tamanhoVetor);
    pegaInstancias(coords, menorDist, tamanhoVetor);
    printf("\nMenor Distancia: %f\n", menorDist);

}


int main(){
    readFile();

    return 0;
}

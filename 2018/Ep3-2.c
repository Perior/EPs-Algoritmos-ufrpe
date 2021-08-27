//Exerc�cio Programa 3 (An�lise Emp�rica de Algoritmos Recursivos)
//Data: 15/07/2018
//Algoritmos e Estruturas de Dados


#include <stdio.h>
#include <stdlib.h>

//Struct que gere um tipo Pontos, que possui duas vari�veis x,y que s�o as coordenadas lidas do arquivo.
typedef struct Pontos{
    int x;
    int y;
}Pontos;


int iniciaJogo(int tamanho, int startX, int startY, int fimX, int fimY, char caminho[], int matriz[][tamanho]){
    static int i = 0;
    if((startX == fimX) && (startY == fimY)){
        return 1;
    }
    char atual = matriz[startX][startY];
    if((matriz[startX][startY] == '0') || startX < 0 || startY < 0){
        return 0;
    }
    else{
        caminho[i] = atual;
        i++;
        if(iniciaJogo(tamanho, startX, startY+1, fimX, fimY, caminho, matriz)){
            return 1;
        }
        else if(iniciaJogo(tamanho, startX+1, startY, fimX, fimY, caminho, matriz)){
            return 1;
        }
        else if(iniciaJogo(tamanho, startX, startY-1, fimX, fimY, caminho, matriz)){
            return 1;
        }
        else if(iniciaJogo(tamanho, startX-1, startY, fimX, fimY, caminho, matriz)){
            return 1;
        }
    }

    return 0;
}


//Fun��o de leitura de arquivo.
int readTamanhoMatriz(){
    int tamanhoMatriz;
    FILE* arquivo = fopen("labirinto.dat", "r");

    if(arquivo == NULL){
        printf("\nNao foi possivel abrir o arquivo!\n\n");
        return;
    }

    fscanf(arquivo, "%d%*c", &tamanhoMatriz);
    fseek(arquivo, 0, SEEK_SET);

    fclose(arquivo);

    return tamanhoMatriz;
}

int stringLenght(int tamanhoMatriz){
    int linha = 1;
    int j = 0;

    FILE* arquivo = fopen("labirinto.dat", "r");

    if(arquivo == NULL){
        printf("\nNao foi possivel abrir o arquivo!\n\n");
        return;
    }

    while(linha != tamanhoMatriz + 4){
        if(fgetc(arquivo) == '\n'){
            linha++;
        }
    }

    while(!feof(arquivo)){
        if(fgetc(arquivo) == 'a'){
            continue;
        }
        fscanf(arquivo, "%*c");
        j++;
    }

    fclose(arquivo);

    return j;
}

Pontos *preencheMatriz(int tamanhoMatriz, int matriz[][tamanhoMatriz], int s[]){
    int linha = 1;
    int j = 0;

    FILE* arquivo = fopen("labirinto.dat", "r");

    if(arquivo == NULL){
        printf("\nNao foi possivel abrir o arquivo!\n\n");
        return;
    }

    Pontos coords[2];

    while(linha < 3){
        if(fgetc(arquivo) == '\n'){
            linha++;
        }
        if(linha == 2){
            fscanf(arquivo, "%d", &coords[0].x);
            fscanf(arquivo, "%d", &coords[0].y);
        }
        if(linha == 3){
            fscanf(arquivo, "%d", &coords[1].x);
            fscanf(arquivo, "%d", &coords[1].y);
        }
    }
    linha = -1;

    while(linha < tamanhoMatriz){
        if(fgetc(arquivo) == '\n'){
            linha++;
            j = 0;
        }
        fscanf(arquivo, "%c", &matriz[linha][j]);
        j++;
    }

    j = 0;

    while(linha == tamanhoMatriz+1){
        fscanf(arquivo, "%c", &s[j]);
        j++;
    }

    fclose(arquivo);

    return coords;
}


int main(){
    int i, j;

    int tamanhoMatriz = readTamanhoMatriz();
    int matriz[tamanhoMatriz][tamanhoMatriz];
    int t = stringLenght(tamanhoMatriz);
    int s[t];
    int *p;
    char caminho[tamanhoMatriz*tamanhoMatriz];

    p = preencheMatriz(tamanhoMatriz, matriz, s);
    int xi = *(p + 0);
    int xf = *(p + 2);
    int yi = *(p + 1);
    int yf = *(p + 3);
    printf("pontos: (%d, %d) inicio e (%d, %d) fim\n", xi, yi, xf, yf);
    if(iniciaJogo(tamanhoMatriz, xi, yi, xf, yf, caminho, matriz)){
        printf("gg\n");
        for(i=0; i<25; i++){
            printf("%c ", caminho[i]);
        }
    }
    else{
        printf("jaja");
    }

    printf("\n");

    for(i=0; i<tamanhoMatriz; i++){
        for(j=0; j<tamanhoMatriz; j++){
            printf("%c", matriz[i][j]);
        }
        printf("\n");
    }


    return 0;
}

/*
    Programa feito por Rita Rezende e Luiz Philippe Amaral
*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void formata_solucao(float **mat, int x, int y){
    int linha_nula;
    int num_solucoes = 1;

    for(int i = 0; i < y ; i++){
        linha_nula = 1;
        for(int j = 0; j < x-1; j++)  {
            if (mat[i][j] != 0) {
                linha_nula = 0;
            }
        }
        if (linha_nula) {
          if (mat[i][x - 1] != 0) {
            num_solucoes = 0;
            break;
          }
          else {
            num_solucoes = -1;
          }
        }
    }
    if(num_solucoes == 1)
        printf("\n\n\nSistema tem solução unica\n\n");
    if (num_solucoes == -1)
        printf("\n\n\nSistema tem infinitas solucoes\n\n");
    if(num_solucoes == 0)
        printf("\n\n\nSistema não tem solucao\n\n");

}

void imprime_matriz(float **mat, int x, int y){
    printf("\nSistema:\n");
    for(int i = 0; i < y; i++){
        for(int j = 0; j < x; j++){
            if( j + 1 != x)
                if(j == 0)
                    printf("%0.1f%c ", mat[i][j], (char)j+65);
                else
                    printf(" + %0.1f%c ", mat[i][j], (char)j+65);
            else
                printf("= %0.1f", mat[i][j]);
        }
        printf("\n");
    }
}

void multiplicar_linha_escalar (float **mat, int x, int y, int linha, float escalar){
    for(size_t i = 0; i < x; i++){
        mat[linha][i] *= escalar;
    }
    printf("\nMultiplicando linha %d por %f:\n", linha, escalar);
    imprime_matriz(mat, x, y);
}

void somar_k_linha (float **mat, int x, int y, int linha1, int linha2, float escalar){
    for(size_t i = 0; i < x; i++){
        mat[linha2][i] += escalar * mat[linha1][i];
    }
    printf("\nSomando linha %d por %0.2f * linha %d:\n", linha1, escalar, linha2);
    imprime_matriz(mat, x, y);
}

void trocar_linha (float **mat, int x, int y, int linha1, int linha2){
    for(size_t i = 0; i < x; i++){
        mat[linha2][i] = mat[linha2][i] + mat[linha1][i];
        mat[linha1][i] = mat[linha2][i] - mat[linha1][i];
        mat[linha2][i] = mat[linha2][i] - mat[linha1][i];
    }
    printf("\nTrocando linha %d por linha %d:\n", linha1, linha2);
    imprime_matriz(mat, x, y);
}

void resolve_sistema(float **mat, int x, int y){
    float pivot = -1;
    int coluna_pivot;

    for(int i = 0; i < y; i++){
        pivot = mat[i][0];
        coluna_pivot = 0;
        for(int j = 0; pivot == 0 && j < x - 1; j++){
            pivot = mat[i][j];
            coluna_pivot = j;
        }
        if(pivot == 0)
            break;
        if(pivot != 1)
            multiplicar_linha_escalar(mat, x, y, i, 1/pivot);
        for(size_t j = 0; j < y; j++){
            if(j != i && mat[j][coluna_pivot] != 0)
                somar_k_linha(mat, x, y, i, j, -mat[j][coluna_pivot]);
        }
    }
    formata_solucao(mat, x, y);
    imprime_matriz(mat, x, y);
}

float **leitor_de_matriz(){

    int x, y;
    printf("Digite a quantidade de variaveis do sistema: ");
    scanf("%d", &x);
    printf("Digite a quantidade de expressões do sistema : ");
    scanf("%d", &y);
    x++;

    float **mat = (float **) malloc(x * sizeof(float));
    for(int i = 0; i < y; i++){
        mat[i] = (float*) malloc(y * sizeof(float));
    }

    for(int i = 0; i < y; i++){
        printf("\nDigite os elementos da matriz extendida expressão por expressão separados por enter: \n");
        for(int j = 0; j < x; j++){
            scanf("%f", &mat[i][j]);
        }
    }

    printf("Matriz estendida:\n");
    imprime_matriz(mat, x, y);
    resolve_sistema(mat, x, y);
    return mat;

}

int main(){

    printf("\nPrograma feito por Rita Rezende Borges de Lima e Luiz Philippe Amaral\n\n\n");
    float **mat = leitor_de_matriz();

    return 0;
}
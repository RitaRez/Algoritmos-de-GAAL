/*
    Programa feito por Rita Rezende e Luiz Philippe Amaral
*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

float verifica_determinante(float **mat, int tam, float det){
    for(int i = 0; i < tam; i++){
        for(int j = 0; j < tam; j++){
            if(i == j)
                det *= mat[i][j];
        }
    }
    return det;
}
void imprime_matriz(float **mat, int tam){
    for(int i = 0; i < tam; i++){
        for(int j = 0; j < tam; j++){
            printf("%0.2f ", mat[i][j]);
        }
        printf("\n");
    }
}

float multiplicar_linha_escalar (float **mat, int x, int y, int linha, float escalar, float det){
    for(size_t i = 0; i < x; i++){
        mat[linha][i] *= escalar;
    }
    printf("\nMultiplicando linha %d por %f:\n", linha, escalar);
    imprime_matriz(mat, x);
    if(det == 0)
        return det + 1/escalar;
    else 
        return det * 1/escalar;

}

float somar_k_linha (float **mat, int x, int y, int linha1, int linha2, float escalar, float det){
    for(size_t i = 0; i < x; i++){
        mat[linha2][i] += escalar * mat[linha1][i];
    }
    printf("\nSomando linha %d por %0.2f * linha %d:\n", linha1, escalar, linha2);
    imprime_matriz(mat, x);

    return det;
}

float trocar_linha (float **mat, int x, int y, int linha1, int linha2, float det){
    for(size_t i = 0; i < x; i++){
        mat[linha2][i] = mat[linha2][i] + mat[linha1][i];
        mat[linha1][i] = mat[linha2][i] - mat[linha1][i];
        mat[linha2][i] = mat[linha2][i] - mat[linha1][i];
    }
    printf("\nTrocando linha %d por linha %d:\n", linha1, linha2);
    imprime_matriz(mat, x);
    return det * -1;
}

void resolve_sistema(float **mat, int x){
    int solucoes;
    float pivot = -1; 
    int coluna_pivot;
    float det = 0;

    for(int i = 0; i < x; i++){
        pivot = mat[i][0];
        coluna_pivot = 0;
        for(int j = 0; pivot == 0 && j < x; j++){
            pivot = mat[i][j];
            coluna_pivot = j;
        }   
        if(pivot == 0)
            break;
        if(pivot != 1)
            det = multiplicar_linha_escalar(mat, x, x, i, 1/pivot, det);
        for(size_t j = 0; j < x; j++){
            if(j != i && mat[j][coluna_pivot] != 0)
                det = somar_k_linha(mat, x, x, i, j, -mat[j][coluna_pivot], det);
        }
    }
    det = verifica_determinante(mat, x, det);
    printf("\n\nDeterminante: %0.2f\n", det);
}

float **leitor_de_matriz(int x){
    
    //Aloca e preenche a matriz que sera invertida
    float **mat = (float **) malloc(x * sizeof(float));
    for(int i = 0; i < x; i++){
        mat[i] = (float*) malloc(x * sizeof(float));
    }

    for(int i = 0; i < x; i++){
        printf("\nDigite os elementos da matriz extendida expressão por expressão separados por enter: \n");
        for(int j = 0; j < x; j++){
            scanf("%f", &mat[i][j]);
        }
    }

    printf("\nMatriz estendida:\n");
    imprime_matriz(mat, x);

    resolve_sistema(mat, x);
    return mat;    

}

int main(){

    printf("\nPrograma feito por Rita Rezende Borges de Lima e Luiz Philippe Amaral\n\n\n");
    int d;
    printf("Digite a dimensão da matriz: ");
    scanf("%d", &d);
    float **mat = leitor_de_matriz(d);

    return 0;
}

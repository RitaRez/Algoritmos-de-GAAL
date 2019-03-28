#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void imprime_matriz(float **mat, int tam){
    for(int i = 0; i < tam; i++){
        for(int j = 0; j < tam; j++){
            printf("%0.2f ", mat[i][j]);
        }
        printf("\n");
    }
}

float determinante(float **mat, int tam){
    
    float det = 0, cofator;
    int i, linha, col, j_aux, i_aux;
    
    if(tam == 1)
        det = mat[0][0];    
    else { 
        
        float **submat = (float **) malloc((tam  - 1) * sizeof(float));
        for(int i = 0; i < tam - 1; i++){
            mat[i] = (float*) malloc((tam - 1) * sizeof(float));
        }

        for(i = 0; i < tam; i++){
            i_aux = 0;
            j_aux = 0;
            for(linha = 1; col < tam; linha++){
                for(col = 0; col < tam; col++){
                    if(col != i){
                        submat[i_aux][j_aux] = mat[linha][col];
                        j_aux++;
                    }
                }
                i_aux++;
                j_aux = 0;
            }

            if(i % 2 == 0)
                cofator = mat[0][i];
            else 
                cofator = mat[0][i];
            det = det + cofator * determinante(submat, tam - 1);
        }
    }
    
    return det;    
            
}

float **leitor_de_matriz(int tam){

    float **mat = (float **) malloc(tam * sizeof(float));
    for(int i = 0; i < tam; i++){
        mat[i] = (float*) malloc(tam * sizeof(float));
    }

    for(int i = 0; i < tam; i++){
        printf("\nDigite os elementos da matriz extendida expressão por expressão separados por enter: \n");
        for(int j = 0; j < tam; j++){
            scanf("%f", &mat[i][j]);
        }
    }

    return mat;

}


int main (){

    int tamanho;
    printf("Digite a dimensão da matriz: ");
    scanf("%d", &tamanho);

    if(tamanho < 0)
        return -1;

    float **mat = leitor_de_matriz(tamanho);
    imprime_matriz(mat, tamanho);
    printf("%f", determinante(mat, tamanho));
    
    return 0;
}
/*
    Programa feito por Rita Rezende e Luiz Philippe Amaral
*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int verifica_identidade(float **mat, int x, int y){
  for (int i = 0; i < y; i++) {
    for(int j = 0; j < x; j++){
      if (i == j && mat[i][j] == 0) return 0;
      if (i != j && mat[i][j] != 0) return 0;
    }
  }
  return 1;
}
void formata_solucao(float **mat, int x, int y){
    
    int linha_nula = verifica_identidade(mat, x - y, y);

    if(linha_nula == 1){
        printf("\n\n\nMatriz invertível\n\n");
        printf("Matriz invertida:\n");    
        for(int i = 0; i < y; i++){
            for(int j = y; j < x; j++){
                printf("%0.1f ", mat[i][j]);
            }
            printf("\n");
        }
    } else {
        printf("\n\n\nA matriz e singular (nao e invertivel)\n");
    }
    
}

void imprime_matriz(float **mat, int x, int y){
    printf("\nSistema:\n");    
    for(int i = 0; i < y; i++){
        for(int j = 0; j < x; j++){
            if( j + y != x)
                if(j == 0)
                    printf("%0.1f ", mat[i][j]);
                else 
                    printf("+ %0.1f ", mat[i][j]);                
            else
                printf("= %0.1f ", mat[i][j]);
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
    int solucoes;
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
}

float **leitor_de_matriz(){
    
    int x, y;
    printf("Digite a quantidade de colunas da matriz: ");
    scanf("%d", &x);
    printf("Digite a quantidade de linhas da matriz: ");
    scanf("%d", &y);
    if(x != y){
        printf("\nA matriz e singular (nao e invertivel)\n");
        exit(-1);
    }
    x += y;

    //Aloca e preenche a matriz que sera invertida
    float **mat = (float **) malloc(x * sizeof(float));
    for(int i = 0; i < y; i++){
        mat[i] = (float*) malloc(y * sizeof(float));
    }

    for(int i = 0; i < y; i++){
        printf("\nDigite os elementos da matriz extendida expressão por expressão separados por enter: \n");
        for(int j = 0; j < x; j++){
            if(j < x - y)
                scanf("%f", &mat[i][j]);
            else
                if(j - y == i)
                    mat[i][j] = 1;
                else       
                    mat[i][j] = 0;
    
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

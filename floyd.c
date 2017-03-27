#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>


void floyd(int *matrix[], int *matrix2[], int nv);

void print_floyd(int *matrix[], int nv);

void checa_ciclos_negativos(int *matrix[], int num_vert);

int main() {

	// Le numero de nos e numero de arestas
	int num_vert, num_arest, a1, a2, p, i, j;

	printf("Digite o numero de vertices e de arestas\n");
	scanf("%d %d", &num_vert, &num_arest);

	/*Criação de matrizes quadradas nxn*/

	int **dist = (int**) malloc (num_vert*sizeof(int*));
	int **pi = (int**) malloc (num_vert*sizeof(int*));	
		
	for(i = 0; i < num_vert; i++){
        dist[i] = (int*) malloc (num_vert*sizeof(int));
        pi[i] = (int*) malloc (num_vert*sizeof(int));
        for(j = 0; j < num_vert; j++){
            dist[i][j] = 1000;
            pi[i][j] = -1;
            if(i == j){
                dist[i][j] = 0;
                pi[i][j] = i;
            }
        }
	}
	
	
    /*Leitura de arestas*/
    
    print_floyd(dist, num_vert);
    print_floyd(pi, num_vert);

    printf("Digite as arestas (A->B) Peso\n");
    printf("No formato: A B P\n");
    for(i = 0; i < num_arest; i++){
        scanf("%d %d %d", &a1, &a2, &p);
        dist[a1][a2] = p;
        pi[a1][a2] = a1;
    }

    printf("Grafo inicial:\n");
    print_floyd(dist, num_vert);

    floyd(dist, pi, num_vert);

    printf("Matriz de distancias:\n");
    print_floyd(dist, num_vert);

    printf("Matriz de predecessores:\n");
    print_floyd(pi, num_vert);

    checa_ciclos_negativos(dist, num_vert);

	free(dist);
	free(pi);
    return 0;
}


void floyd(int *dist[], int*pi[], int nv){
    int k, i, j;
    for(k = 0; k < nv; k++){
        for(i = 0; i < nv; i++){
            for(j = 0; j < nv; j++){
                if(dist[i][j] > dist[i][k] + dist[k][j]){
                    dist[i][j] = dist[i][k] + dist[k][j];
                    pi[i][j] = pi[k][j];
                }
            }
        }
    }
}

void print_floyd(int *matrix[], int nv){
    int i, j;
    for(i = 0; i < nv; i++){
        for(j = 0; j < nv; j++){
            printf("%5d     ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void checa_ciclos_negativos(int *matrix[], int nv){
    int i, k = 0;
    for(i = 0; i < nv; i++){
        if(matrix[i][i] < 0){
            k = 1;
        }
    }
    if(k == 1){
        printf("Existe 1 ou mais ciclos negativos no grafo\n");
    }
    else{
        printf("Nao existem ciclos negativos no grafo\n");
    }
}

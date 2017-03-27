#include <vector>
#include <iostream>
#include <cstdlib>
using namespace std;

void floyd(int *dist[], int nv){
    int k, i, j;
    for(k = 0; k < nv; k++){
        for(i = 0; i < nv; i++){
            for(j = 0; j < nv; j++){
                if(dist[i][j] > dist[i][k] + dist[k][j]){
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
}

int cmpInt (const void * a, const void * b) {
	return ( *(int*)a - *(int*)b );
}

int checkDegrees (int **m1, int **m2, int n)
{
	int in1 [n];
	int in2 [n];
	int out1 [n];
	int out2 [n];

	//Inicialização (trocar por calloc)
	for(int i = 0; i < n; i++) {
		in1[i] = 0;
		in2[i] = 0;
		out1[i] = 0;
		out2[i] = 0;
	}
	
	/*                 */
	/* DEGREE SEQUENCE */
	/*                 */
	
	//Cria vetores de in/out a partir da matriz de adj
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			int val1 = m1[i][j];
			int val2 = m2[i][j];
			
			in1[j] += val1;
			out1[i] += val1;
			
			in2[j] += val2;
			out2[i] += val2;
		}
	}
	
	int classe1 [n];
	int classe2 [n];
	
	//Inicialização (trocar por calloc)
	for(int i = 0; i < n; i++)  {
		classe1[i] = 0;
		classe2[i] = 0;
	}
	
	int cl_n = 0; //classe
	
	for(int i = 0; i < n; i++) {
		int cl_i = in1[i];
		int cl_o = out1[i];
		
		if(classe1[i] != 0)
			continue;
			
		cl_n++;
		
		for(int j = 0; j < n; j++) {
			if(classe2[j] != 0)
				continue;
			
			if((cl_i == in2[j]) && (cl_o == out2[j]))
				classe2[j] = cl_n;
		}
	}
	
	qsort(classe1, n, sizeof(int), cmpInt);
	qsort(classe2, n, sizeof(int), cmpInt);
	
	for(int i = 0; i < n; i++) {
		if(classe1[i] != classe2[i])
			return 0;
	}
	return 1;
}


int main ()
{
	int n_vert, n_arest;
	
	cout << "Numero de vertices: ";
	cin >> n_vert;
	
	cout << "Numero de arestas: ";
	cin >> n_arest;
	
	//cout << "n_vert : " << n_vert << endl;
	//cout << "n_arest : " << n_arest << endl;
	
	/*Aloca as matrizes*/
	int **adj1 = new int* [n_vert];
	int **adj2 = new int* [n_vert];
	int **dist1 = new int* [n_vert];
	int **dist2 = new int* [n_vert];
	for(int i = 0; i < n_vert; i++) {
		adj1[i] = new int [n_vert];
		adj2[i] = new int [n_vert];
	}
	
	
	/*Zera as matrizes*/
	for(int i = 0; i < n_vert; i++)
		for(int j = 0; j < n_vert; j++) {
			adj1[i][j] = 0;
			adj2[i][j] = 0;
		}
			
	/*Le as matrizes*/
	int u,v;
	for(int i = 0; i < n_arest; i++) {
		cin >> u;
		cin >> v;
		adj1[u][v] = 1;
	}
	for(int i = 0; i < n_arest; i++) {
		cin >> u;
		cin >> v;
		adj2[u][v] = 1;
	}
	
	/*Imprime as matrizes*/
	cout << "Matriz 1\n";
	for(int i = 0; i < n_vert; i++) {
		for(int j = 0; j < n_vert; j++)
			cout << adj1[i][j] << " ";
		cout << "\n";
	}
	cout << "\nMatriz 2\n";
	for(int i = 0; i < n_vert; i++) {
		for(int j = 0; j < n_vert; j++)
			cout << adj2[i][j] << " ";
		cout << "\n";
	}
	
	int grau = checkDegrees(adj1, adj2, n_vert);
	if(grau)
		cout << "Os grafos possuem mesma sequencia de graus\n";
	else {
		cout << "Os grafos não são isomorfos\n";
		return 0;
	}
	
	
	
	/*Desaloca as matrizes*/
	for(int i = 0; i < n_vert; i++) {
		delete [] adj1[i];
		delete [] adj2[i];
	}
	delete [] adj1;
	delete [] adj2;
	
	return 0;
}

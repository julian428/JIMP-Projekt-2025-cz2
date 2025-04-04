#include "graph.h"

void printSparseMatrix(Node* sparse_matrix, int vertesies, int edges){
	for(int i = 0, n = 0; i < vertesies*vertesies; i++){
		int val = 0;
		if(i == sparse_matrix[n].position) val = sparse_matrix[n++].value;
		if(i % vertesies == 0) printf("\n");
		printf("%2d ", val);
	}
	printf("\n");
}

Node* sparseMatrixToLaplacian(Node* sparce_matrix, int vertesies, int edges){
	int* degree_vector = (int*)calloc(vertesies, sizeof(int));
	for(int i = 0; i < edges; i++){
		int node_row = sparce_matrix[i].position / vertesies;
		degree_vector[node_row]++;
	}

	Node* laplacian = (Node*)malloc((edges + vertesies) * sizeof(Node));

	int deg = 0, lap = 0;
	for(int n = 0; deg < vertesies && n < edges; lap++){
		int node_row = sparce_matrix[n].position / vertesies;
		int node_column = sparce_matrix[n].position % vertesies;

		if(deg < node_row || node_column > node_row && node_row == deg){
			laplacian[lap].position = deg*vertesies + deg;
			laplacian[lap].value = degree_vector[deg++];
		}
		else{
			laplacian[lap].position = sparce_matrix[n].position;
			laplacian[lap].value = -sparce_matrix[n++].value;
		}
	}

	while(deg < vertesies){
		laplacian[lap].position = deg * vertesies + deg;
		laplacian[lap++].value = degree_vector[deg++];
	}
	
	free(degree_vector);
	return laplacian;
}

int* getEigenSmallestVectors(){
	return NULL;
}


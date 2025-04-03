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

	for(int deg = 0, n = 0, i = 0; deg < vertesies && n < edges; i++){
		int node_row = sparce_matrix[n].position / vertesies;
		int node_column = sparce_matrix[n].position % vertesies;

		if(deg < node_row || node_column > node_row && node_row == deg){
			laplacian[i].position = deg*vertesies + deg;
			laplacian[i].value = degree_vector[deg++];
		}
		else{
			laplacian[i].position = sparce_matrix[n].position;
			laplacian[i].value = -sparce_matrix[n++].value;
		}
	}

	free(degree_vector);
	return laplacian;
}


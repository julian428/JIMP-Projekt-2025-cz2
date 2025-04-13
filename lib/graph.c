#include "graph.h"

Node* sparseMatrixToLaplacian(Node* sparce_matrix, int vertesies, int edges){
	int* degree_vector = (int*)calloc(vertesies, sizeof(int));
	if(!degree_vector){
		fprintf(stderr, "\tNie udało się zaalokować pamięci na wektor diagonalny. graph.c:sparseMatrixToLaplacian\n");
		return NULL;
	}

	for(int i = 0; i < edges; i++){
		int node_row = sparce_matrix[i].position / vertesies;
		degree_vector[node_row]++;
	}

	Node* laplacian = (Node*)malloc((edges + vertesies) * sizeof(Node));
	if(!laplacian){
		fprintf(stderr, "\tNie udało się zaalokować pamięci na macierz Laplace'a. graph.c:sparseMatrixToLaplacian\n");
		free(degree_vector);
		return NULL;
	}

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

Node *makeSymmetric(Node *sparse_matrix, int nodes, int edges, int *new_size) {
  int capacity = edges * 2;
  Node *symmetric_array = (Node *)malloc(capacity * sizeof(Node));
  if (!symmetric_array) {
    fprintf(stderr, "Nie udało się zaalokować pamięci na powiększoną macierz symetryczną. graph.c:makeSymmetric\n");
    return NULL;
  }

	for(int i = 0; i < capacity; i+=2){
		symmetric_array[i] = sparse_matrix[i/2];
		symmetric_array[i+1].value = sparse_matrix[i/2].value;
		symmetric_array[i+1].position = (sparse_matrix[i/2].position % nodes) * nodes + sparse_matrix[i/2].position / nodes;
	}

	*new_size = capacity;
	
	qsort(symmetric_array, capacity, sizeof(Node), comparenodes);

  return symmetric_array;
}

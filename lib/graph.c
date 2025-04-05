#include "graph.h"

void printSparseMatrix(Node* sparse_matrix, int vertesies, int edges){
	if(vertesies > 10){
		printf("Matrix too large to print.\nPrinting only edges.\n");
		for(int i = 0; i < edges; i++){
			printf("{ row: %d; col: %d; val: %d; pos: %d }\n", sparse_matrix[i].position / vertesies, sparse_matrix[i].position % vertesies, sparse_matrix[i].value, sparse_matrix[i].position);
		}
		return;
	}

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

int comparenodes(const void *a, const void *b) {
    return ((Node*)a)->position - ((Node*)b)->position;
}

int compareEigenNodes(const void *a, const void *b) {
    double diff = ((EigenNode *)a)->value - ((EigenNode *)b)->value;
    return (diff > 0) - (diff < 0); // Returns -1, 0, or 1
}

void clusterEigenvector(FILE* output_file, double *eigenvector, int size, int k, double percentage) {
	// zaminiam podaną tablice wektorową na tablicę struct-ów
    EigenNode *nodes = (EigenNode *)malloc(size * sizeof(EigenNode));
    if (!nodes) {
        fprintf(stderr, "Nie udało się zaalokować pamięci na wektor własny.\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < size; i++) {
        nodes[i].index = i;
        nodes[i].value = eigenvector[i];
    }

    qsort(nodes, size, sizeof(EigenNode), compareEigenNodes);

    int idealSize = size / k;
    int minSize = (int)(idealSize * (1 - percentage / 100.0));
    int maxSize = (int)(idealSize * (1 + percentage / 100.0));

    int count = 0, clusterCount = 0;

    for (int i = 0; i < size; i++) {
        fprintf(output_file, "%d ", nodes[i].index);
        count++;

        if (count >= idealSize && clusterCount < k - 1) {
            fprintf(output_file, "\n");
            count = 0;
            clusterCount++;
        }
    }
    fprintf(output_file, "\n");

    free(nodes);
}

#include "graph.h"

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

int findEdge(Node *array, int n, int position) {
    int left = 0, right = n - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (array[mid].position == position) return mid;
        if (array[mid].position < position) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

Node *makeSymmetric(Node *array, int n, int matrix_size, int *newSize) {
  int capacity = n * 2;
  Node *symmetricArray = (Node *)malloc(capacity * sizeof(Node));
  if (!symmetricArray) {
    fprintf(stderr, "Nie udało się zaalokować pamięci na powiększoną macierz symetryczną.\n");
    exit(EXIT_FAILURE);
  }

	for(int i = 0; i < capacity; i+=2){
		symmetricArray[i] = array[i/2];
		symmetricArray[i+1].value = array[i/2].value;
		symmetricArray[i+1].position = (array[i/2].position % matrix_size) * matrix_size + array[i/2].position / matrix_size;
	}

	*newSize = capacity;
	
	qsort(symmetricArray, capacity, sizeof(Node), comparenodes);

  return symmetricArray;
}

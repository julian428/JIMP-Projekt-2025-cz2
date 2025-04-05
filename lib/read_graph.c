#include "read_graph.h"

int createGraphFile(char* input_file, char* output_file){
	char buffer[512];
	sprintf(buffer, "./jimp2/projekt-4/bin/graphdecoder %s > %s", input_file, output_file);
	return system(buffer);
}

int countNodesInFile(FILE* file){
	char ch;
	int nodes = 0;
	int newline = 0;
	while(ch = fgetc(file)){
		if(ch == '\n') newline = 1;
		else if(!newline && ch == '1') nodes++;
		else if(newline && ch != ' ') break; // linijka z macierzą zawsze zaczyna się od spacji
		else newline = 0;
	}
	fseek(file, ftell(file)-1, SEEK_SET); // cofam sie bo odczytał pierwszy znak z połączeń
	return nodes;
}

Node* fileToSparseMatrix(FILE* file, int* foreign_nodes, int* foreign_edges){
	int nodes = countNodesInFile(file);
	int from, to;
	long start_of_edges = ftell(file);
	int edges = 0;
	while(fscanf(file, " %d - %d\n", &from, &to) == 2) edges++; // licze ile krawędzi

	fseek(file, start_of_edges, SEEK_SET); // wracam na początek deklaracji krawędzi
	Node* sparse_matrix = (Node*)malloc(edges * sizeof(Node));
	for(int i = 0; fscanf(file, " %d - %d\n", &from, &to) == 2; i++){
		sparse_matrix[i].value = 1;
		sparse_matrix[i].position = from * nodes + to;
	}
	
	*foreign_nodes = nodes;
	*foreign_edges = edges;
	return sparse_matrix;
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

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
	int from, to, s;
	long start_of_edges = ftell(file);
	int edges = 0;
	while((s = fscanf(file, " %d - %d\n", &from, &to)) == 2) edges++; // licze ile krawędzi

	fseek(file, start_of_edges, SEEK_SET); // wracam na początek deklaracji krawędzi
	Node* sparse_matrix = (Node*)malloc(edges * sizeof(Node));
	for(int i = 0; (s = fscanf(file, " %d - %d\n", &from, &to)) == 2; i++){
		sparse_matrix[i].value = 1;
		sparse_matrix[i].position = from * edges + to;
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
	// sortuje żeby wyszukiwanie binarne dobrze działało
    qsort(array, n, sizeof(Node), comparenodes);

    int capacity = n * 2;
    Node *symmetricArray = (Node *)malloc(capacity * sizeof(Node));
    if (!symmetricArray) {
        fprintf(stderr, "Nie udało się zaalokować pamięci na powiększoną macierz symetryczną.\n");
        exit(EXIT_FAILURE);
    }

    int count = 0;

    for (int i = 0; i < n; i++) {
        symmetricArray[count++] = array[i];

        int row = array[i].position / matrix_size;
        int col = array[i].position % matrix_size;

        int symmetric_position = col * matrix_size + row;

        // Sprawdzam czy jest symetria z aktualnym punktem
        if (findEdge(array, n, symmetric_position) == -1) {
            if (count >= capacity) {
                capacity *= 2;
                symmetricArray = (Node *)realloc(symmetricArray, capacity * sizeof(Node));
                if (!symmetricArray) {
                    fprintf(stderr, "Nie udało się zwiększyć pamięci dla symetrycznej macierzy.\n");
                    exit(EXIT_FAILURE);
                }
            }
            Node newNode;
            newNode.value = array[i].value;
            newNode.position = symmetric_position;
            symmetricArray[count++] = newNode;
        }
    }

    // Zmniejszam rozmiar tablicy na odpowiednią
    *newSize = count;
    symmetricArray = (Node *)realloc(symmetricArray, count * sizeof(Node));

    return symmetricArray;
}

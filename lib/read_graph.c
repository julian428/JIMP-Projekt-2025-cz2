#include "read_graph.h"

int createGraphFile(char* input_file, char* output_file){
	char buffer[512];
	sprintf(buffer, "./jimp2/projekt-4/bin/graphdecoder %s > %s", input_file, output_file);
	return system(buffer);
}

int createGraphFile2(char* input_file, char* output_file){
	char buffer[512];
	sprintf(buffer, "./jimp2/projekt-4/bin/translate %s %s", input_file, output_file);
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

void clusterEigenvector(FILE* output_file, double *eigenvector, int size, int k, double percentage) {
	// zaminiam podaną tablice wektorową na tablicę struct-ów
  EigenNode *nodes = (EigenNode *)malloc(size * sizeof(EigenNode));
  if (!nodes) {
    conditionalPrintf("\tNie udało się zaalokować pamięci na wektor własny.\n");
		return;
  }
  for (int i = 0; i < size; i++) {
    nodes[i].index = i;
    nodes[i].value = eigenvector[i];
  }

  qsort(nodes, size, sizeof(EigenNode), compareEigenNodes);

  int idealSize = size / k;
	int freeNodes = size % k;

  int count = 0, clusterCount = 0;

  for (int i = 0; i < size; i++) {
    fprintf(output_file, "%d ", nodes[i].index);
    count++;

    if (count >= idealSize && clusterCount < k - 1) {
			if(freeNodes > 0 && i < size - 2){
				double distanceLeft = fabs(nodes[i+1].value-nodes[i].value);
				double distanceRight = fabs(nodes[i+2].value-nodes[i+1].value);

				if(distanceLeft < distanceRight){
					fprintf(output_file, "%d ", nodes[++i].index);
					freeNodes--;
				}
			}
      fprintf(output_file, "\n");
      count = 0;
      clusterCount++;
    }
  }
  fprintf(output_file, "\n");

  free(nodes);
}

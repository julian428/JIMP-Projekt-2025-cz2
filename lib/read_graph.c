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

void clusterEigenvector(FILE* output_file, double *eigenvector, int eigenvector_size, int cluster_count, double percentage) {
    EigenNode *nodes = (EigenNode*)malloc(eigenvector_size * sizeof(EigenNode));
    if (!nodes) {
        fprintf(stderr, "Nie udało się zaalokować pamięci na wektor wierzchołków.\tclusterEigenvector:read_graph.c\n");
        return;
    }

    for (int i = 0; i < eigenvector_size; i++) {
        nodes[i].index = i;
        nodes[i].value = eigenvector[i];
    }

    qsort(nodes, eigenvector_size, sizeof(EigenNode), compareEigenNodes);

    int ideal_cluster_size = eigenvector_size / cluster_count;
    double max_cluster_size = ceil(ideal_cluster_size * (1 + percentage / 100.0));
    int remainder = eigenvector_size % cluster_count;

		fprintf(output_file, "nodes:%d clusters:%d percentage:%lf cluster_size:%d\n", eigenvector_size, cluster_count, percentage, ideal_cluster_size);

    int current_index = 0;
    for (int c = 0; c < cluster_count; c++) {
        int cluster_size = ideal_cluster_size + (remainder > 0 ? 1 : 0);
        if (cluster_size > max_cluster_size) {
            cluster_size = (int)max_cluster_size;
        }
        remainder--;

        for (int j = 0; j < cluster_size && current_index < eigenvector_size; j++) {
            fprintf(output_file, "%d ", nodes[current_index].index);
            current_index++;
        }
        fprintf(output_file, "\n");
    }

    free(nodes);
}

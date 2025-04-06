#include "lib/graph.h"
#include "lib/graph_math.h"
#include "lib/read_graph.h"
#include "lib/utils.h"

#include <stdio.h>

int main(int argc, char** argv){
	int nodes = 0;
	int edges = 0;	
	char* output_file = "clusters.txt";
	char* input_file = "jimp2/projekt-4/dane/graf.csrrg";
	int cluster_count = 2;
	double percentage = 10.0;

	// start parametrów

	char* new_output_file = getParameter(argc, argv, "-o");
	char* new_input_file = getParameter(argc, argv, "-i");
	char* new_cluster_count = getParameter(argc, argv, "-c");
	char* new_percentage = getParameter(argc, argv, "-p");

	if(new_output_file) output_file = new_output_file;
	if(new_input_file) input_file = new_input_file;
	if(new_cluster_count) cluster_count = atoi(new_cluster_count);
	if(new_percentage) percentage = atof(new_percentage);

	// koniec parametrów
	
	int res = createGraphFile(input_file, "output.txt");
	if(res != 0) return 1;

	// start przygotowania macierzy sąsiedztwa

	FILE* file = fopen("output.txt", "r");
	Node* adjc = fileToSparseMatrix(file, &nodes, &edges);
	fclose(file);

	int new_edges = 0;
	adjc = makeSymmetric(adjc, nodes, edges, &new_edges);
	edges = new_edges;

	Node* laplacian = sparseMatrixToLaplacian(adjc, nodes, edges);
	free(adjc);
	edges += nodes;

  qsort(laplacian, edges, sizeof(Node), comparenodes);

	// koniec przygotowywania
	
	double* eigenvector = inversePowerIteration(laplacian, nodes, edges);
	FILE* clusters_file = fopen(output_file, "w");
  clusterEigenvector(clusters_file, eigenvector, nodes, cluster_count, percentage);

	fclose(clusters_file);
  free(eigenvector);
	free(laplacian);
	return 0;
}

#include "lib/graph.h"
#include "lib/graph_math.h"
#include "lib/read_graph.h"
#include "lib/utils.h"

#include <stdio.h>

int main(int argc, char** argv){
	int nodes = 6;
	int edges = 16;	
	char* output_file = "clusters.txt";
	char* input_file = "jimp2/projekt-4/dane/graf.csrrg";
	int cluster_count = 2;
	double percentage = 10.0;

	char* new_output_file = getParameter(argc, argv, "-o");
	char* new_input_file = getParameter(argc, argv, "-i");
	char* new_cluster_count = getParameter(argc, argv, "-c");
	char* new_percentage = getParameter(argc, argv, "-p");

	if(new_output_file) output_file = new_output_file;
	if(new_input_file) input_file = new_input_file;
	if(new_cluster_count) cluster_count = atoi(new_cluster_count);
	if(new_percentage) percentage = atof(new_percentage);
	
	int res = createGraphFile(input_file, "output.txt");
	if(res != 0) return 1;

	FILE* file = fopen("output.txt", "r");
	Node* adjc = fileToSparseMatrix(file, &nodes, &edges);
	printSparseMatrix(adjc, nodes, edges);

	int new_edges = 0;
	adjc = makeSymmetric(adjc, edges, nodes, &new_edges);
	edges = new_edges;
	printSparseMatrix(adjc, nodes, edges);

	Node* laplacian = sparseMatrixToLaplacian(adjc, nodes, edges);
  qsort(laplacian, edges, sizeof(Node), comparenodes);
	printSparseMatrix(laplacian, nodes, edges);
	
	double *eigenvector = malloc(nodes * sizeof(double));
  double eigenvalue;

  inversePowerMethod(laplacian, edges, eigenvector, &eigenvalue, nodes);

	FILE* clusters_file = fopen(output_file, "w");
  clusterEigenvector(clusters_file, eigenvector, nodes, cluster_count, percentage);

	fclose(file);
	fclose(cluster_file);
  free(eigenvector);
	free(adjc);
	free(laplacian);
	return 0;
}

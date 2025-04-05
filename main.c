#include "lib/graph.h"
#include "lib/graph_math.h"
#include "lib/read_graph.h"
#include "lib/utils.h"

#include <stdio.h>

int main(int argc, char** argv){
	int nodes = 6;
	int edges = 16;	
	char* output_file = "output.txt";
	char* input_file = "jimp2/projekt-4/dane/graf.csrrg";
	int cluster_count = 2;
	double percentage = 10.0;
	/*Node* adjc = (Node*)calloc(edges, sizeof(Node));

	adjc[0].value = 1; adjc[0].position = 1;
	adjc[1].value = 1; adjc[1].position = 2;
	adjc[2].value = 1; adjc[2].position = 6;
	adjc[3].value = 1; adjc[3].position = 8;
	adjc[4].value = 1; adjc[4].position = 10;
	adjc[5].value = 1; adjc[5].position = 12;
	adjc[6].value = 1; adjc[6].position = 13;
	adjc[7].value = 1; adjc[7].position = 15;
	adjc[8].value = 1; adjc[8].position = 20;
	adjc[9].value = 1; adjc[9].position = 22;
	adjc[10].value = 1; adjc[10].position = 23;
	adjc[11].value = 1; adjc[11].position = 25;
	adjc[12].value = 1; adjc[12].position = 27;
	adjc[13].value = 1; adjc[13].position = 29;
	adjc[14].value = 1; adjc[14].position = 33;
	adjc[15].value = 1; adjc[15].position = 34;*/

	char* new_output_file = getParameter(argc, argv, "-o");
	char* new_input_file = getParameter(argc, argv, "-i");
	char* new_cluster_count = getParameter(argc, argv, "-c");
	char* new_percentage = getParameter(argc, argv, "-p");

	if(new_output_file) output_file = new_output_file;
	if(new_input_file) input_file = new_input_file;
	if(new_cluster_count) cluster_count = atoi(new_cluster_count);
	if(new_percentage) percentage = atof(new_percentage);
	
	createGraphFile(input_file, output_file);

	FILE* file = fopen(output_file, "r");
	Node* adjc = fileToSparseMatrix(file, &nodes, &edges);
	int new_edges = 0;
	adjc = makeSymmetric(adjc, edges, nodes, &new_edges);
	edges = new_edges;

	Node* laplacian = sparseMatrixToLaplacian(adjc, nodes, edges);
  qsort(laplacian, edges, sizeof(Node), comparenodes);
	
	double *eigenvector = malloc(nodes * sizeof(double));
  double eigenvalue;

  inversePowerMethod(laplacian, edges, eigenvector, &eigenvalue, nodes);

  clusterEigenvector(eigenvector, nodes, cluster_count, percentage);

  free(eigenvector);
	free(adjc);
	free(laplacian);
	return 0;
}

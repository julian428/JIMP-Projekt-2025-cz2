#include "lib/graph.h"
#include "lib/graph_math.h"
#include "lib/read_graph.h"
#include "lib/utils.h"
#include "lib/visualize_graph.h"

#include <stdio.h>

int LOG = 0;

int main(int argc, char** argv){
	int nodes = 0;
	int edges = 0;	
	char* output_file = "clusters.txt";
	char* input_file = "jimp2/projekt-4/dane/graf.csrrg";
	char* dot_file = "clusters.dot";
	int generate_dot = 0;
	int cluster_count = 2;
	double percentage = 10.0;

	// start parametrów

	char* new_output_file = getParameter(argc, argv, "-o");
	char* new_input_file = getParameter(argc, argv, "-i");
	char* new_cluster_count = getParameter(argc, argv, "-c");
	char* new_percentage = getParameter(argc, argv, "-p");
	char* new_log = getParameter(argc, argv, "-l");
	char* new_dot_file = getParameter(argc, argv, "-g");

	if(new_output_file) output_file = new_output_file;
	if(new_input_file) input_file = new_input_file;
	if(new_cluster_count) cluster_count = atoi(new_cluster_count);
	if(new_percentage) percentage = atof(new_percentage);
	if(new_log) LOG = 1;
	if(new_dot_file){
		generate_dot = 1;
		dot_file = new_dot_file;
	}

	if(percentage > 100) percentage = 100;
	if(percentage < 0) percentage = 0;
	if(cluster_count < 1) cluster_count = 1;

	// koniec parametrów
	
	int res = createGraphFile2(input_file, "output.txt");
	if(res != 0){
		conditionalPrintf("\tNie udało się przetłumaczyć pliku \"%s\".\n", input_file);
		return 1;
	}

	// start przygotowania macierzy sąsiedztwa

	FILE* file = fopen("output.txt", "r");
	if(!file){
		conditionalPrintf("\tNie udało się otworzyć pliku \"output.txt\"\n");
		return 1;
	}

	Node* adjc = fileToSparseMatrix(file, &nodes, &edges);
	if(!adjc) {
		conditionalPrintf("\tNie udało się stworzyć macierzy rzadkiej sąsiedztwa.\n");
		fclose(file);
		return 1;
	}
	if(cluster_count > nodes) cluster_count = nodes;
	conditionalPrintf("wierzchołki: %d\nkrawędzie: %d\n", nodes, edges);

	fclose(file);
  qsort(adjc, edges, sizeof(Node), comparenodes);
	conditionalPrintf("Pierwotna macierz sąsiedztwa:\n");
	printSparseMatrix(adjc, nodes, edges);

	int new_edges = 0;
	adjc = makeSymmetric(adjc, nodes, edges, &new_edges);
	edges = new_edges;
	if(!adjc){
		conditionalPrintf("\tNie udało się zsymetralizować macierzy rzadkiej.\n");
		return 1;
	}
	conditionalPrintf("Symetryczna macierz sąsiedztwa:\nNowa ilość krawędzi: %d\n", edges);
	printSparseMatrix(adjc, nodes, edges);

	Node* laplacian = sparseMatrixToLaplacian(adjc, nodes, edges);
	if(!laplacian){
		conditionalPrintf("\tNie udało się stworzyć macierzy Laplace'a.\n");
		free(adjc);
		return 1;
	}
	free(adjc);
	edges += nodes;
	conditionalPrintf("Macierz Laplace'a:\nNowa ilość krawędzi: %d\n", edges);
	printSparseMatrix(laplacian, nodes, edges);

  qsort(laplacian, edges, sizeof(Node), comparenodes);

	// koniec przygotowywania

	double* eigenvector = inversePowerIteration(laplacian, nodes, edges);
	if(!eigenvector){
		conditionalPrintf("\tNie udało się znaleźć wektora własnego.\n");
		return 1;
	}

	FILE* clusters_file = fopen(output_file, "w");
	if(!clusters_file){
		conditionalPrintf("\tNie udało się otworzyć pliku \"%s\" do zapisania klastrów.\n", output_file);
		free(eigenvector);
		return 1;
	}

  clusterEigenvector(clusters_file, eigenvector, nodes, cluster_count, percentage);
	fclose(clusters_file);

	if(generate_dot){
		createDotFile("output.txt", output_file, dot_file, cluster_count);
	}

  free(eigenvector);
	free(laplacian);
	return 0;
}

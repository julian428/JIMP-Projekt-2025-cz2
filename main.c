#include "lib/graph.h"

int main(int argc, char** argv){
	int nodes = 6;
	int edges = 16;	
	Node* adjc = (Node*)calloc(edges, sizeof(Node));

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
	adjc[15].value = 1; adjc[15].position = 34;

	printSparseMatrix(adjc, nodes, edges);

	Node* laplacian = sparseMatrixToLaplacian(adjc, nodes, edges);
	printSparseMatrix(laplacian, nodes, edges);

	free(adjc);
	free(laplacian);
	return 0;
}

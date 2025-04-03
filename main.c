#include "lib/graph.h"

int main(int argc, char** argv){
	Node* adjc;
	adjc->value = 0;
	adjc->position = 1;
	adjc->next = NULL;

	addNode(adjc, 1, 2);
	addNode(adjc, 2, 6);
	addNode(adjc, 3, 8);
	addNode(adjc, 4, 10);
	addNode(adjc, 5, 12);
	addNode(adjc, 6, 13);
	addNode(adjc, 7, 15);
	addNode(adjc, 8, 20);
	addNode(adjc, 9, 22);
	addNode(adjc, 10, 23);
	addNode(adjc, 11, 25);
	addNode(adjc, 12, 27);
	addNode(adjc, 13, 29);
	addNode(adjc, 14, 33);
	addNode(adjc, 15, 34);

	int edges = 6;

	printf("Original Matrix:\n");
	printNodesAsMatrix(adjc, edges);

	//printf("Transposed Matrix:\n");
	//Node* transposed_adjc = transposeNodes(adjc, edges);
	//printNodesAsMatrix(transposed_adjc, edges);

	//printf("Combined Matrices:\n");
	//Node* added_nodes = addMatrixNodes(adjc, transposed_adjc, edges);
	//printNodesAsMatrix(added_nodes, edges);

	printf("Laplacian Matrix:\n");
	Node* laplace_matrix = graphToLaplacian(adjc, edges);
	printNodesAsMatrix(laplace_matrix, edges); 

	return 0;
}

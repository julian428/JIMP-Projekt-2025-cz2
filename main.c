#include "lib/graph.h"

int main(int argc, char** argv){
	Node* adjc;
	adjc->value = 0;
	adjc->position = 1;
	adjc->next = NULL;

	addNode(adjc, 1, 7);
	addNode(adjc, 2, 13);

	printf("Original Matrix:\n");
	printNodesAsMatrix(adjc, 4);

	printf("Transposed Matrix:\n");
	Node* transposed_adjc = transposeNodes(adjc, 4);
	printNodesAsMatrix(transposed_adjc, 4);

	printf("Combined Matrices:\n");
	Node* added_nodes = addMatrixNodes(adjc, transposed_adjc, 4);
	printNodesAsMatrix(added_nodes, 4);

	printf("Laplacian Matrix:\n");
	Node* laplace_matrix = graphToLaplacian(added_nodes, 4);
	printNodesAsMatrix(laplace_matrix, 4);

	return 0;
}

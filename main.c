#include "lib/graph.h"

int main(int argc, char** argv){
	Node adjc = { 0, 1, NULL };
	addNode(&adjc, 1, 7);
	addNode(&adjc, 2, 13);
	printNodesAsMatrix(&adjc, 4);
	Node* transposed_adjc = transposeNodes(&adjc, 4);
	printNodesAsMatrix(transposed_adjc, 4);
	Node* added_nodes = addMatrixNodes(&adjc, transposed_adjc, 4);
	printNodesAsMatrix(added_nodes, 4);
	Node* laplace_matrix = graphToLaplacian(added_nodes, 4);
	printNodesAsMatrix(laplace_matrix, 4);

	return 0;
}

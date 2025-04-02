#include "lib/graph.h"

int main(int argc, char** argv){
	Node adjc = { 0, 1, NULL };
	addNode(&adjc, 1, 7);
	addNode(&adjc, 2, 13);
	printNodesAsMatrix(&adjc, 4);
	Node* laplace_matrix = graphToLaplacian(&adjc, 4);
	printNodesAsMatrix(laplace_matrix, 4);
	while(laplace_matrix){
		printf("%d -> ", laplace_matrix->value);
		laplace_matrix = laplace_matrix->next;
	}

	return 0;
}

#include "lib/graph.h"

int main(int argc, char** argv){
	Node adjc = { 1, 1, NULL };
	addNode(&adjc, 1, 7);
	printNodesAsMatrix(&adjc, 3);
	Node* laplaceMatrix = graphToLaplacian(&adjc, 3);
	printNodesAsMatrix(laplaceMatrix, 3);

	return 0;
}

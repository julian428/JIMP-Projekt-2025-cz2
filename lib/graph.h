#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Node_ {
	int value;
	int position; // Position in 1D array
} Node;

void printSparseMatrix(Node* nodes, int vertesies, int edges);
Node* sparseMatrixToLaplacian(Node* sparce_matrix, int vertesies, int edges);

#endif

#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Node_ {
	int value;
	int position; // Position in 1D array
	struct Node_ *next;
} Node;

Node* graphToLaplacian(Node* adjecency_matrix, int edges);
Node* addNode(Node* first_node, int value, int position);
Node* transposeNodes(Node* first_node, int edges);
Node* addMatrixNodes(Node* start_a, Node* start_b, int edges);
void printNodesAsMatrix(Node* first_node, int edges);

#endif

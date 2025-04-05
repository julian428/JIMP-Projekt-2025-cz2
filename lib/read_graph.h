#ifndef READ_GRAPH_H
#define READ_GRAPH_H

#include <stdio.h>

#include "graph.h"

int countNodesInFile(FILE* file);
Node* fileToSparseMatrix(FILE* file, int* foreign_nodes, int* foreign_edges);
int findEdge(Node *array, int n, int position);
Node *makeSymmetric(Node *array, int n, int matrix_size, int *newSize);
void createGraphFile();

#endif

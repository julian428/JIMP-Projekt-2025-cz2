#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct Node_ {
	int value;
	int position; // pozycja w jedno wymiarowej tabeli sąsiedztwa
} Node;

typedef struct {
    int index; // oryginalny index w tabeli
    double value;
} EigenNode;

#include "read_graph.h"

void printSparseMatrix(Node* nodes, int vertesies, int edges);
Node* sparseMatrixToLaplacian(Node* sparce_matrix, int vertesies, int edges);
int comparenodes(const void *a, const void *b);
int compareEigenNodes(const void *a, const void *b);
void clusterEigenvector(double *eigenvector, int size, int k, double percentage);

#endif

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
    double x;
		double y;
		int cluster;
} EigenNode;

#include "read_graph.h"
#include "utils.h"

Node* sparseMatrixToLaplacian(Node* sparce_matrix, int vertesies, int edges);
int findEdge(Node *array, int n, int position);
Node *makeSymmetric(Node *array, int n, int matrix_size, int *newSize);

#endif

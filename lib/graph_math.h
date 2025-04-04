#ifndef GRAPH_MATH_H
#define GRAPH_MATH_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "graph.h"

#define TOL 1e-6
#define MAX_ITER 1000

void solveSparseSystem(Node *matrix, int nnz, double *b, double *x, int n);
void normalize(double *v, int n);
double dotProduct(double *v1, double *v2, int n);
void inversePowerMethod(Node *matrix, int nnz, double *eigenvector, double *eigenvalue, int n);

#endif

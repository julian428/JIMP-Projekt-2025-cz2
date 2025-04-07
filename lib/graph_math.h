#ifndef GRAPH_MATH_H
#define GRAPH_MATH_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "graph.h"

#define TOL 1e-6
#define MAX_ITER 1000
#define EPSILON 0.1

double normalizedVectorDifference(double* a, double* b, int nodes);
void normalizeVector(double* vector, int nodes);
double* gaussSeidelSolver(Node* sparse_matrix, int nodes, int edges, double* x);
double* inversePowerIteration(Node* sparse_matrix, int nodes, int edges);

#endif

#ifndef READ_GRAPH_H
#define READ_GRAPH_H

#include <stdio.h>

#include "graph.h"

int countNodesInFile(FILE* file);
Node* fileToSparseMatrix(FILE* file, int* foreign_nodes, int* foreign_edges);
int createGraphFile(char* input_file, char* output_file);
int createGraphFile2(char* input_file, char* output_file);
void clusterEigenvector(FILE* output_file, double *eigenvector, int eigenvector_size, int cluster_count, double percentage);

#endif

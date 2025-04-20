#ifndef READ_GRAPH_H
#define READ_GRAPH_H

#include <stdio.h>

#include "graph.h"

int countNodesInFile(FILE* file);
Node* fileToSparseMatrix(FILE* file, int* foreign_nodes, int* foreign_edges);
int createGraphFile(char* input_file, char* output_file);
int createGraphFile2(char* input_file, char* output_file);
void clusterEigenvector(FILE* output_file, EigenNode *eigen_nodes, int nodes, int edges, int cluster_count, double percentage);

#endif

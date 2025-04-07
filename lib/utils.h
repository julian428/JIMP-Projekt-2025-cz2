#ifndef UTILS_H
#define UTILS_H

#include<stdio.h>
#include<string.h>
#include<stdarg.h>

#include "graph.h"

extern int LOG;

char* getParameter(int param_count, char** params, char* param_prefix);
void printSparseMatrix(Node* sparse_matrix, int vertesies, int edges);
int comparenodes(const void *a, const void *b);
int compareEigenNodes(const void *a, const void *b);
void conditionalPrintf(const char *format, ...);

#endif

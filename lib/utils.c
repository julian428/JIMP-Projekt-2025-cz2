#include "utils.h"

char* getParameter(int param_count, char** params, char* param_prefix){
	for(int i = 1; i < param_count-1; i++){
		if(!strcmp(params[i], param_prefix)) return params[i+1];
	}
	return NULL;
}

void printSparseMatrix(Node* sparse_matrix, int vertesies, int edges){
	if(vertesies > 10){
		printf("Matrix too large to print.\n");
		/*for(int i = 0; i < edges; i++){
			printf("{ row: %d; col: %d; val: %d; pos: %d }\n", sparse_matrix[i].position / vertesies, sparse_matrix[i].position % vertesies, sparse_matrix[i].value, sparse_matrix[i].position);
		}*/
		return;
	}

	for(int i = 0, n = 0; i < vertesies*vertesies; i++){
		int val = 0;
		if(i == sparse_matrix[n].position) val = sparse_matrix[n++].value;
		if(i % vertesies == 0) printf("\n");
		printf("%2d ", val);
	}
	printf("\n");
}

int comparenodes(const void *a, const void *b) {
    return ((Node*)a)->position - ((Node*)b)->position;
}

int compareEigenNodes(const void *a, const void *b) {
    double diff = ((EigenNode *)a)->value - ((EigenNode *)b)->value;
    return (diff > 0) - (diff < 0); // Returns -1, 0, or 1
}



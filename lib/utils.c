#include "utils.h"

char* getParameter(int param_count, char** params, char* param_prefix){
	for(int i = 1; i < param_count-1; i++){
		if(!strcmp(params[i], param_prefix)) return params[i+1];
	}
	return NULL;
}

void printSparseMatrix(Node* sparse_matrix, int vertesies, int edges){
	if(vertesies > 10){
		return;
	}

	for(int i = 0, n = 0; i < vertesies*vertesies; i++){
		int val = 0;
		if(i == sparse_matrix[n].position) val = sparse_matrix[n++].value;
		if(i % vertesies == 0) conditionalPrintf("\t\n\t");
		conditionalPrintf("%2d ", val);
	}
	conditionalPrintf("\n");
}

int comparenodes(const void *a, const void *b) {
    return ((Node*)a)->position - ((Node*)b)->position;
}

int compareEigenNodes(const void *a, const void *b) {
    double diff = ((EigenNode *)a)->value - ((EigenNode *)b)->value;
    return (diff > 0) - (diff < 0);
}

void conditionalPrintf(const char *format, ...) {
  va_list args;
	if(LOG == 0) return;

  va_start(args, format);
  vprintf(format, args);
  va_end(args);

}

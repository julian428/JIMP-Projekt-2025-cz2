#include "utils.h"

char* getParameter(int param_count, char** params, char* param_prefix){
	for(int i = 1; i < param_count-1; i++){
		if(!strcmp(params[i], param_prefix)) return params[i+1];
	}
	return NULL;
}

int comparenodes(const void *a, const void *b) {
    return ((Node*)a)->position - ((Node*)b)->position;
}

int compareEigenNodes(const void *a, const void *b) {
	int clusterA = ((EigenNode *)a)->cluster;
	int clusterB = ((EigenNode *)b)->cluster;
  return (clusterA > clusterB) - (clusterA < clusterB);
}

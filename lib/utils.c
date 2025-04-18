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
    double len_x = ((EigenNode *)a)->x - ((EigenNode *)b)->x;
    double len_y = ((EigenNode *)a)->y - ((EigenNode *)b)->y;
    return (len_x > 0) - (len_x < 0);
}

#include "lib/utils.h"
#include <stdio.h>
#include <limits.h>
#include <math.h>
#include <string.h>

int getNextNumberInFile(FILE* file, int *f_number){// f_number - zmienna podana do nadpisania
	char ch;
	int number = 0;
	if((ch = fgetc(file)) == EOF) return 0;

	do{
		if(ch > '9' || ch < '0') break;
		number *= 10;
		number += ch - '0';
		ch = fgetc(file);
	}while(ch == EOF || (ch <= '9' && ch >= '0') );

	if(ch == '\n') return 2;

	*f_number = number;

	return 1;
}

char* getParameter(int param_count, char** params, char* param_prefix){
	for(int i = 1; i < param_count-1; i++){
		if(!strcmp(params[i], param_prefix)) return params[i+1];
	}
	return NULL;
}

int main(int argc, char** argv){
	char* file_name = "clusters.txt";
	int cluster_count = 2;

	char* new_file_name = getParameter(argc, argv, "-o");
	char* new_cluster_count = getParameter(argc, argv, "-c");
	if(new_file_name) file_name = new_file_name;
	if(new_cluster_count) cluster_count = atoi(new_cluster_count);

	FILE* file = fopen(file_name, "r");
	if(!file) return 1;

	int node;
	int node_count = -cluster_count;
	int max_node_number = -INT_MAX;
	while(getNextNumberInFile(file, &node)){
		if(node > max_node_number) max_node_number = node;
		node_count++;
	}

	printf("Wierzchołki w klastrach: %d\nOminięte wierzchołki: %d\n\n", node_count, node_count - max_node_number - 1);
	
	printf("Sprawdzenie klastrów:\n");
	int ideal_cluster_size = node_count/cluster_count;
	printf("Idealny rozmiar klastra: %d\n\n", ideal_cluster_size);
	rewind(file);
	for(int cluster = 0; cluster < cluster_count; cluster++){
		int current_node_count = 0;
		while(getNextNumberInFile(file, &node) == 1){
			if((node_count / cluster_count) < 21)	printf("%d ", node);
			current_node_count++;
		}
		double size_difference_percentage = round(((double)current_node_count/ideal_cluster_size - 1)*100);
		printf(";\033[1m%d wierzchołków -> zmiana = %.0lf%\033[0m\n", current_node_count, size_difference_percentage);
	}

	fclose(file);
}

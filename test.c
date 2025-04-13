#include <stdio.h>
#include <stdlib.h>
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

int testFile(char* file_name){
	FILE* file = fopen(file_name, "r");
	if(!file) return 1;

	int node_count, cluster_count, ideal_cluster_size;
	double percentage;
	if(fscanf(file, "nodes:%d clusters:%d percentage:%lf cluster_size:%d\n", &node_count, &cluster_count, &percentage, &ideal_cluster_size) != 4){
		fprintf(stderr, "Zły format pierwszej linijki w pliku %s", file_name);
		return 1;
	}

	double minimum_percentage = ((double)(ideal_cluster_size+1) / ideal_cluster_size - 1) * 100;
	int warning = 0;

	for(int cluster = 0; cluster < cluster_count; cluster++){
		int current_node_count = 0;
		int node;
		while(getNextNumberInFile(file, &node) == 1) current_node_count++;

		double size_difference_percentage = ((double)current_node_count/ideal_cluster_size - 1)*100;
		if(size_difference_percentage > fmax(percentage, minimum_percentage)) return 2;
		else if(size_difference_percentage <= minimum_percentage && size_difference_percentage > percentage) warning = 1;
	}

	fclose(file);
	return warning;
}

int main(int argc, char** argv){
	char* file_name = "clusters.txt";
	int test_count = 1;
	for(int i = 0; i < test_count; i++){
		int test_result = testFile(file_name);
		char* message = test_result == 2 ? "\x1B[31mFAILURE\x1B[0m" : test_result == 1 ? "\x1B[33mWARNING\x1B[0m" : "\x1B[32mSUCCESS\x1B[0m";
		printf("%s. %s\n", message, file_name);
	}
}

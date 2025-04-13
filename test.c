#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <string.h>

#define TEST_COUNT 6

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
	int prime_numbers[TEST_COUNT] = {7, 19, 43, 61, 71, 89};

	for(int i = 0; i < TEST_COUNT; i++){
		char buffer[64];
		sprintf(buffer, "./bin/divide_graph -i jimp2/projekt-4/dane/graf%d.csrrg -c %d", i+1, prime_numbers[i]);
		int result = system(buffer);
		if(result != 0) return 1;

		int test_result = testFile("clusters.txt");

		char* message = test_result == 2 ? "\x1B[31mFAILURE\x1B[0m" : test_result == 1 ? "\x1B[33mWARNING\x1B[0m" : "\x1B[32mSUCCESS\x1B[0m";
		printf("%s. graf%d.csrrg\n", message, i+1);
	}
	system("rm clusters.txt");
}

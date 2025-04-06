#include "graph_math.h"

int getValueAtPosition(Node* sparse_matrix, int edges, int position){
	for(int i = 0; i < edges; i++){
		if(sparse_matrix[i].position != position) continue;
		return sparse_matrix[i].value;
	}

	return 0;
}

double normalizedVectorDifference(double* a, double* b, int nodes){
	double sum = 0;
	for(int i = 0; i < nodes; i++){
		double diff = a[i] - b[i];
		sum += diff * diff;
	}

	return sqrt(sum);
}

void normalizeVector(double* vector, int nodes){
	double norm = 0;
	for(int i = 0; i < nodes; i++) norm += vector[i] * vector[i];
	norm = sqrt(norm);

	if(norm == 0) return;
	for(int i = 0; i < nodes; i++) vector[i] /= norm;
}

double* gaussSeidelSolver(Node* sparse_matrix, int nodes, int edges, double* x){
	double *solution = calloc(nodes, sizeof(double));
	double *previous_solution = calloc(nodes, sizeof(double));

	for(int i = 0; i < MAX_ITER; i++){
		for(int n = 0; n < nodes; n++){
			double diagonal_value = (double)getValueAtPosition(sparse_matrix, edges, n * nodes + n);
			if(diagonal_value == 0) diagonal_value = EPSILON;
			
			double sum = 0;
			for(int j = 0; j < nodes; j++){
				if(j == n) continue;
				int value = getValueAtPosition(sparse_matrix, edges, n * nodes + j);
				if(value == 0) continue;
				sum += value * solution[j];
			}

			solution[n] = (x[n] - sum) / diagonal_value;
		}

		double err = normalizedVectorDifference(solution, previous_solution, nodes);
		if(err < TOL) break;

		for(int j = 0; j < nodes; j++) previous_solution[j] = solution[j];
	}

	free(previous_solution);
	return solution;
}

double* inversePowerIteration(Node* sparse_matrix, int nodes, int edges){
	srand(time(NULL));
	double* eigenvector = malloc(nodes * sizeof(double));
	double* previous_eigenvector = malloc(nodes * sizeof(double));

	// losowy wektor start
	double mean = 0;
	for(int i = 0; i < nodes; i++){
		eigenvector[i] = (double)(rand()%100) - 50;
		mean += eigenvector[i];
	}

	mean /= nodes;
	for(int i = 0; i < nodes; i++) eigenvector[i] -= mean;
	normalizeVector(eigenvector, nodes);
	// losowy wektor end
	
	for(int i = 0; i < MAX_ITER; i++){
		for(int n = 0; n < nodes; n++) previous_eigenvector[n] = eigenvector[n];
		double* new_guess = gaussSeidelSolver(sparse_matrix, nodes, edges, previous_eigenvector);

		normalizeVector(new_guess, nodes);
		for(int n = 0; n < nodes; n++) eigenvector[n] = new_guess[n];
		free(new_guess);

		double err = normalizedVectorDifference(eigenvector, previous_eigenvector, nodes);
		if(err < TOL) break;
	}

	free(previous_eigenvector);
	return eigenvector;
}

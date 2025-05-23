#include "graph_math.h"

// @complexity O(nodes)
double normalizedVectorDifference(double* a, double* b, int nodes){
	double sum = 0;
	for(int i = 0; i < nodes; i++){
		double diff = a[i] - b[i];
		sum += diff * diff;
	}

	return sqrt(sum);
}

// @complexity O(nodes)
double dotProduct(double* a, double* b, int nodes) {
    double dot = 0;
    for (int i = 0; i < nodes; i++) {
        dot += a[i] * b[i];
    }
    return dot;
}

// @complexity O(nodes)
void normalizeVector(double* vector, int nodes){
	double norm = 0;
	for(int i = 0; i < nodes; i++) norm += vector[i] * vector[i];
	norm = sqrt(norm);

	if(norm == 0) return;
	for(int i = 0; i < nodes; i++) vector[i] /= norm;
}

// @complexity O(nodes)
void substractMean(double* vector, int nodes) {
    double sum = 0.0;
    for (int i = 0; i < nodes; i++) sum += vector[i];
    double mean = sum / nodes;
    for (int i = 0; i < nodes; i++) vector[i] -= mean;
}

// @complexity O(edges)
double* gaussSeidelSolver(Node* sparse_matrix, int nodes, int edges, double* x, double sigma){
	double *solution = calloc(nodes, sizeof(double));
	if(!solution){
		fprintf(stderr, "\tNie udało się zaalokować pamięci na wektor wynikowy. graph_math.c:gaussSeidelSolver\n");
		return NULL;
	}

	double *previous_solution = calloc(nodes, sizeof(double));
	if(!previous_solution){
		fprintf(stderr, "\tNie udało się zaalokować pamięci dla wektora pomocniczego. graph_math.c:gaussSeidelSolver\n");
		free(solution);
		return NULL;
	}

	for(int i = 0; i < MAX_ITER; i++){
		double diagonal_value = 1;
		double sum = 0;
		int current_row = 0;
		for(int j = 0; j < edges; j++){
			double value = sparse_matrix[j].value;
			int position = sparse_matrix[j].position;
			int row = position / nodes;
			int column = position % nodes;

			if(diagonal_value == 0){
				diagonal_value = 1;
				fprintf(stderr, "\tNapotkano wartość diagonalną w wierszu %d na pozycji absolutnej %d.\n", row, position);
			}

			if(current_row < row){
				solution[current_row] = (x[current_row] - sum) / diagonal_value;
				sum = 0;
				current_row++;
			}

			if(row == column){
				//printf("diag_val: %lf, sigma: %lf, illegal: %lf\n", value, sigma, value - 2.5);
				diagonal_value = value - sigma;
				continue;
			}

			sum += value * solution[column];
		}

		solution[current_row] = (x[current_row] - sum) / diagonal_value;


		double err = normalizedVectorDifference(solution, previous_solution, nodes);
		if(err < TOL){
			break;
		}

		for(int j = 0; j < nodes; j++) previous_solution[j] = solution[j];
	}

	free(previous_solution);
	return solution;
}

// @complexity O(edges)
double* inversePowerIteration(Node* sparse_matrix, int nodes, int edges, double* skip_vector, double sigma){
	srand(time(NULL));
	double* eigenvector = malloc(nodes * sizeof(double));
	if(!eigenvector){
		fprintf(stderr, "\tNie udało się zaalokować pamięci na wektor własny. graph_math.c:inversePowerIteration\n");
		return NULL;
	}

	double* previous_eigenvector = malloc(nodes * sizeof(double));
	if(!previous_eigenvector){
		fprintf(stderr, "Nie udało się zaalokować pamięci na pomocniczy wektor własny. graph_math.c:inversePowerIteration");
	}

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
		double* new_guess = gaussSeidelSolver(sparse_matrix, nodes, edges, previous_eigenvector, sigma);

		if(skip_vector){
			double dot = dotProduct(new_guess, skip_vector, nodes);
			for(int i = 0; i < nodes; i++){
				new_guess[i] -= dot * skip_vector[i];
			}
		}

		substractMean(new_guess, nodes);
		normalizeVector(new_guess, nodes);
		for(int n = 0; n < nodes; n++) eigenvector[n] = new_guess[n];
		free(new_guess);

		double err = normalizedVectorDifference(eigenvector, previous_eigenvector, nodes);
		
		if(err < TOL){
			break;
		}
	}

	free(previous_eigenvector);
	return eigenvector;
}

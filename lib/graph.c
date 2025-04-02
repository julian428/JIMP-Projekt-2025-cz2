#include "graph.h"

Node* graphToLaplacian(Node* adjecency_matrix, int edges){
	int* degree_vector = (int*)calloc(edges, sizeof(int));
	Node* matrix_start = adjecency_matrix;

	while(adjecency_matrix){
		int current_row = adjecency_matrix->position / edges;
		degree_vector[current_row]++;
		adjecency_matrix = adjecency_matrix->next;
	}

	Node* laplace_start = (Node*)malloc(sizeof(Node));
	laplace_start->position = 0;
	laplace_start->value = degree_vector[0];
	laplace_start->next = NULL;

	int added_degree = 1;
	while(matrix_start){
		int current_row = matrix_start->position/edges;
		int current_column = matrix_start->position % edges;
		
		if((added_degree == current_row && current_column > current_row) || added_degree < current_row){
			degree_vector[added_degree] && addNode(laplace_start, degree_vector[added_degree], added_degree*edges+added_degree);
			added_degree++;
			continue;
		}

		addNode(laplace_start, -1, matrix_start->position);
		matrix_start = matrix_start->next;
	}

	for(;added_degree < edges; added_degree++){
		addNode(laplace_start, degree_vector[added_degree], added_degree*edges + added_degree);
	}

	free(degree_vector);
	return laplace_start;
}

Node* addNode(Node* first_node, int value, int position){
	Node* new_node = (Node*)malloc(sizeof(Node));
	new_node->value=value;
	new_node->position = position;
	new_node->next=NULL;

	while(first_node->next != NULL) first_node = first_node->next;
	first_node->next = new_node;
	return new_node;
}

void printNodesAsMatrix(Node* first_node, int edges){
	for(int i = 0; i < edges*edges; i++){
		int val = 0;
		if(first_node && first_node->position == i) {
			val = 1;
			first_node = first_node->next;
		}
		if(i % edges == 0) printf("\n");
		printf("%d ", val);
	}
	printf("\n");
}

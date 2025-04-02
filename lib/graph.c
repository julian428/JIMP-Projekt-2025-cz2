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

Node* transposeNodes(Node* first_node, int edges){
	Node* t_nodes= (Node*)malloc(sizeof(Node));
	t_nodes->value = first_node->value;
	t_nodes->position = (first_node->position % edges)*edges + first_node->position / edges;
	t_nodes->next = NULL;
	first_node = first_node->next;

	while(first_node){
		int row = first_node->position / edges;
		int column = first_node->position % edges;

		addNode(t_nodes, first_node->value, column*edges + row);
		first_node = first_node->next;
	}

	return t_nodes;
}

Node* addMatrixNodes(Node* start_a, Node* start_b, int edges){
	Node* combined_nodes = (Node*)malloc(sizeof(Node));

	while(start_a && start_b){
		int a_pos = start_a->position;
		int b_pos = start_b->position;

		if(a_pos > b_pos){
			addNode(combined_nodes, start_b->value, b_pos);
			start_b = start_b->next;
		}else{
			addNode(combined_nodes, start_a->value, a_pos);
			start_a = start_a->next;
		}
	}

	return combined_nodes;
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


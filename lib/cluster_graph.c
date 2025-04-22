#include "cluster_graph.h"

double distance(EigenNode a, EigenNode b){
	double squareX = pow(a.x - b.x, 2);
	double squareY = pow(a.y - b.y, 2);

	double d = sqrt(squareX + squareY);
	return d;
}

int assignClusters(EigenNode *nodes, EigenNode *centroids, int node_count, int cluster_count, double percentage){
	int changed = 0;
	int max_size = (int)((1.0 + percentage) * (node_count / cluster_count));

	for(int i = 0; i < node_count; i++){
		double minimum_distance = distance(nodes[i], centroids[0]);
		int assigned_cluster = 0;

		for(int j = 1; j < cluster_count; j++){
			double current_distance = distance(nodes[i], centroids[j]);
			if(current_distance > minimum_distance) continue;
			minimum_distance = current_distance;
			assigned_cluster = j;
		}

		if(nodes[i].cluster != assigned_cluster){
			nodes[i].cluster = assigned_cluster;
			changed = 1;
		}
	}

	return changed;
}

void updateCentroids(EigenNode *nodes, EigenNode *centroids, int node_count, int cluster_count){
	double *sumX = (double*)calloc(cluster_count, sizeof(double));
	double *sumY = (double*)calloc(cluster_count, sizeof(double));
	int *count = (int*)calloc(cluster_count, sizeof(int));

	for(int i = 0; i < node_count; i++){
		int cluster = nodes[i].cluster;
		sumX[cluster] += nodes[i].x;
		sumY[cluster] += nodes[i].y;
		count[cluster]++;
	}

	for(int i = 0; i < cluster_count; i++){
		if(count[i] == 0) continue;
		centroids[i].x = sumX[i] / count[i];
		centroids[i].y = sumY[i] / count[i];
	}

	free(sumX);
	free(sumY);
	free(count);
}

void meanClustering(EigenNode *nodes, int node_count, int cluster_count, double percentage){
	EigenNode *centroids = (EigenNode*)malloc(cluster_count * sizeof(EigenNode));

	for(int i = 0; i < cluster_count; i++) centroids[i] = nodes[i];

	int changed = 1;
	for(int i = 0; changed && i < MAX_ITER; i++){
		changed = assignClusters(nodes, centroids, node_count, cluster_count, percentage);
		updateCentroids(nodes, centroids, node_count, cluster_count);
	}
}

#include "cluster_graph.h"

double distance(EigenNode a, EigenNode b){
	double squareX = pow(a.x - b.x, 2);
	double squareY = pow(a.y - b.y, 2);

	double d = sqrt(squareX + squareY);
	return d;
}

int assignClusters(EigenNode *nodes, EigenNode *centroids, int node_count, int cluster_count, double percentage) {
	int changed = 0;
	int max_size = (int)((1.0 + percentage) * (node_count / cluster_count));
	int *cluster_counts = (int*)calloc(cluster_count, sizeof(int));

	// wypełnienie ilości wierzchołków w klastrach
	for (int i = 0; i < node_count; i++) {
		int cluster = nodes[i].cluster;
		if(cluster < 0) continue;
		cluster_counts[cluster]++;
	}

	for (int i = 0; i < node_count; i++) {
		int best_cluster = rand() % cluster_count;
		double best_distance = DBL_MAX;

		for (int j = 0; j < cluster_count; j++) {
			if (cluster_counts[j] >= max_size && j != nodes[i].cluster) continue;

			double dist = distance(nodes[i], centroids[j]);
			if (dist < best_distance) {
				best_distance = dist;
				best_cluster = j;
			}
		}

		if (best_cluster != nodes[i].cluster) {
			int previous_cluster = nodes[i].cluster;
			if(previous_cluster >= 0) cluster_counts[nodes[i].cluster]--;
			cluster_counts[best_cluster]++;
			nodes[i].cluster = best_cluster;
			changed = 1;
		}
	}

	free(cluster_counts);
	return changed;
}

void updateCentroids(EigenNode *nodes, EigenNode *centroids, int node_count, int cluster_count){
	double *sumX = (double*)calloc(cluster_count, sizeof(double));
	double *sumY = (double*)calloc(cluster_count, sizeof(double));
	int *count = (int*)calloc(cluster_count, sizeof(int));

	for(int i = 0; i < node_count; i++){
		int cluster = nodes[i].cluster;
		if(cluster < 0) continue;
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
	int cluster_size = node_count / cluster_count;

	for(int i = 0; i < cluster_count; i++) centroids[i] = nodes[i*cluster_size];

	int changed = 1;
	for(int i = 0; changed && i < MAX_ITER; i++){
		changed = assignClusters(nodes, centroids, node_count, cluster_count, percentage);
		updateCentroids(nodes, centroids, node_count, cluster_count);
	}
}

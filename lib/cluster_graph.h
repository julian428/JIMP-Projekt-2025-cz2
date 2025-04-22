#ifndef CLUSTER_GRAPH_H
#define CLUSTER_GRAPH_H

#define MAX_ITER 1000

#include<math.h>
#include<float.h>
#include "graph.h"

void meanClustering(EigenNode *nodes, int node_count, int cluster_count, double percentage);

#endif

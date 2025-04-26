#include "visualize_graph.h"

void createDotFile(char* clusters_file_name, char* dotfile_name){
	FILE* clusters_file = fopen(clusters_file_name, "r");
	FILE* dotfile = fopen(dotfile_name, "w");
	if(!dotfile){
		return;
	}

	int nodes, edges, clusters, cluster_size;
	double percentage;
	if(fscanf(clusters_file, "nodes:%d edges:%d clusters:%d percentage:%lf cluster_size:%d", &nodes, &edges, &clusters, &percentage, &cluster_size) != 5){
		return;
	}

	char* colors[] = {"pink", "green", "blue", "yellow"};

	fprintf(dotfile, "digraph Regiony {\n");

	char ch;
	for (int row = 0; row < clusters; row++) {
    fprintf(dotfile, "\tsubgraph cluster_%d {\n\t\tlabel = \"Region %d\";\n\t\tstyle = filled;\n\t\tcolor = %s;\n\t\tnode [style=filled, color=white];\n\t\t", row, row+1, colors[row%4]);

    ch = fgetc(clusters_file);
    if (ch == EOF) break;

		int is_cluster_number = 1;
    do {
        if (ch == ' ') {
            fprintf(dotfile, "; ");
						is_cluster_number = 1;
				} else if(is_cluster_number && ch == ';') {
					is_cluster_number = 0;
        } else if (ch != '\n' && ch != EOF && is_cluster_number) {
						printf("%c\n", ch);
            fprintf(dotfile, "%c", ch);
        }
        ch = fgetc(clusters_file);
    } while (ch != '\n' && ch != EOF);

    fprintf(dotfile, "\n\t}\n");
	}

	int from, to;
	while(fscanf(clusters_file, "%d -> %d\n", &from, &to) == 2){
		fprintf(dotfile, "\t%d -> %d;\n", from, to);
	}

	fprintf(dotfile, "}\n");

	fclose(dotfile);
}

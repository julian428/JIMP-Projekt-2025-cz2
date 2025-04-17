#include "visualize_graph.h"


int skipPositionalMatrix(FILE* matrix_file){
    int newline = 0;
    char ch;

    while ((ch = fgetc(matrix_file)) != EOF) {
        if (ch == '\n') {
            newline = 1;
        } else if (newline && ch != ' ') {
            fseek(matrix_file, -1, SEEK_CUR);
            return 0;
        } else {
            newline = 0;
        }
    }

    return 1;
}

void skipLine(FILE *file) {
    int ch;
    while ((ch = fgetc(file)) != '\n' && ch != EOF);
}

void createDotFile(char* connectionsfile_name, char* clusterfile_name, char* dotfile_name, int clusters){
	FILE* cluster_file = fopen(clusterfile_name, "r");
	if(!cluster_file) return;
	skipLine(cluster_file);
	
	FILE* dotfile = fopen(dotfile_name, "w");
	if(!dotfile){
		fclose(cluster_file);
		return;
	}

	char* colors[] = {"pink", "green", "blue", "yellow"};

	fprintf(dotfile, "digraph Regiony {\n");

	char ch;
	for (int row = 0; row < clusters; row++) {
    fprintf(dotfile, "\tsubgraph cluster_%d {\n\t\tlabel = \"Region %d\";\n\t\tstyle = filled;\n\t\tcolor = %s;\n\t\tnode [style=filled, color=white];\n\t\t", row, row+1, colors[row%4]);

    ch = fgetc(cluster_file);
    if (ch == EOF) break;

    do {
        if (ch == ' ') {
            fprintf(dotfile, "; ");
        } else if (ch != '\n' && ch != EOF) {
            fprintf(dotfile, "%c", ch);
        }
        ch = fgetc(cluster_file);
    } while (ch != '\n' && ch != EOF);

    fprintf(dotfile, "\n\t}\n");
	}

	FILE* connectionsfile = fopen(connectionsfile_name, "r");
	if(!connectionsfile){
		fprintf(dotfile, "}\n");
		fclose(cluster_file);
		fclose(dotfile);
		return;
	}

	skipPositionalMatrix(connectionsfile);

	int from, to;
	while(fscanf(connectionsfile, "%d - %d\n", &from, &to) == 2){
		fprintf(dotfile, "\t%d -> %d;\n", from, to);
	}

	fprintf(dotfile, "}\n");

	fclose(connectionsfile);
	fclose(cluster_file);
	fclose(dotfile);
}

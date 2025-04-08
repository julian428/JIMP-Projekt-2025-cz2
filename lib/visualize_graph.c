#include "visualize_graph.h"

void createDotFile(char* clusterfile_name, char* dotfile_name, int clusters){
	FILE* cluster_file = fopen(clusterfile_name, "r");
	if(!cluster_file) return;
	
	FILE* dotfile = fopen(dotfile_name, "w");
	if(!dotfile){
		fclose(cluster_file);
		return;
	}

	fprintf(dotfile, "digraph R {\n");

	char ch;
	for (int row = 0; row < clusters; row++) {
    fprintf(dotfile, "\tsubgraph cluster_%d {\n\t\tlabel = \"Region %d\";\n\t\tstyle = filled;\n\t\tcolor = lightblue;\n\t\tnode [style=filled, color=white];\n\t\t", row, row+1);

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


	fprintf(dotfile, "}\n");

	fclose(cluster_file);
	fclose(dotfile);
}

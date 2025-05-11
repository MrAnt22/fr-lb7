#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024

int main(int argc, char *argv[]){
	if (argc != 3){
		fprintf(stderr, "Usage: %s <word> <filename>\n", argv[0]);
		return 1;
	}

	const char *word = argv[1];
	const char *filename = argv[2];

	FILE *file = fopen(filename, "r");
	if (!file){
		perror("fopen");
		return 1;
	}

	char line[MAX_LINE];
	while(fgets(line, sizeof(line), file)){
		if(strstr(line,word)){
			printf("%s",line);
		}
	}

	fclose(file);
	return 0;
}


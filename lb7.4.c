#include <stdio.h>
#include <stdlib.h>

#define PAGE_SIZE 20

void wait_for_key(){
	printf("-Press Enter to continue-");
	while(getchar() != '\n');
}

void show_file(const char *filename){
	FILE *file = fopen(filename, "r");
	if (!file){
		perror(filename);
		return;
	}

	char line[1024];
	int count = 0;

	while(fgets(line, sizeof(line), file)){
		printf("%s", line);
		count++;
	
		if (count == PAGE_SIZE){
			wait_for_key();
			count = 0;
		}
	}

	fclose(file);
}

int main(int argc, char *argv[]){
	if(argc < 2){
		fprintf(stderr, "Usage: %s file1 [file2...]\n", argv[0]);
		return 1;
	}

	for (int i = 1;i < argc;i++){
		printf("====%s====\n",argv[i]);
		show_file(argv[i]);
	}
	return 0;
}



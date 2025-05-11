#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <ctype.h>

int is_regular_file(const char *path){
	struct stat st;
	return (stat(path, &st) == 0) && S_ISREG(st.st_mode);
}

void ask_and_delete(const char *filename){
	char response[10];
	printf("Delete file \"%s\"? (y/n): ",filename);
	if (fgets(response, sizeof(response),stdin)){
		if (tolower(response[0]) == 'y'){
			if(remove(filename) == 0){
				printf("Deleted: %s\n", filename);
			}
			else{
				perror("Error during deleting");
			}
		}
		else{
			printf("Skiped %s\n", filename);
		}
	}
}

int main(){
	DIR *dp;
	struct dirent *entry;
	
	dp = opendir(".");
	if (!dp){
		perror("opendir");
		return 1;
	}

	while ((entry = readdir(dp)) != NULL){
		if (entry->d_type == DT_REG || is_regular_file(entry->d_name)){
			ask_and_delete(entry->d_name);
		}
	}
	closedir(dp);
	return 0;
}

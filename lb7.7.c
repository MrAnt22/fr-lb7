#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ctype.h>

int is_executable_file(const char *filename){
	struct stat st;
	if (stat(filename, &st) != 0)
		return 0;
	return (st.st_mode & S_IXUSR) && S_ISREG(st.st_mode);
}

void ask_and_grant(const char *filename){
	char response[10];
	printf("File: %s - open for writing? (y/n)", filename);
	if (fgets(response, sizeof(response), stdin)){
		if (tolower(response[0]) == 'y'){
			if (chmod(filename, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IROTH | S_IXGRP | S_IXOTH) == 0){
				printf("Allowed for reading %s\n", filename);
			}
			else{
				perror("chmod");
			}
		}
		else{
			printf("Skiped: %s\n", filename);
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
		if (entry->d_type == DT_REG && is_executable_file(entry->d_name)){
			ask_and_grant(entry->d_name);
		}
	}

	closedir(dp);
	return 0;
}

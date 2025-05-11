#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_ENTRIES 1024

int is_directory(const char *name){
	struct stat st;
	return (stat(name, &st) == 0 && S_ISDIR(st.st_mode));
}

int compare(const void *a, const void *b){
	return strcmp(*(const char **)a, *(const char **)b);
}

int main(){
	DIR *dp;
	struct dirent *entry;
	char *subdirs[MAX_ENTRIES];
	int count = 0;

	dp = opendir(".");
	if (dp == NULL){
		perror("opendir");
		return 1;
	}

	while ((entry = readdir(dp)) != NULL){
		if (entry->d_type == DT_DIR){
			if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
				continue;
			subdirs[count++] = strdup(entry->d_name);
			if(count >= MAX_ENTRIES)
				break;
		}
	}
	closedir(dp);

	qsort(subdirs, count, sizeof(char *), compare);

	printf("Subdirectories (sorted):\n");
	for (int i = 0;i < count;i++){
		printf("%s\n", subdirs[i]);
		free(subdirs[i]);
	}
	return 0;
}





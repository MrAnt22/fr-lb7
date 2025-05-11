#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

void list_dir(const char *path){
	struct dirent *entry;
	DIR *dp = opendir(path);
	
	if(dp == NULL){
		perror(path);
		return;
	}

	while ((entry = readdir(dp)) != NULL){
		if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
			continue;

		char fullpath[1024];
		snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);

		printf("%s\n", fullpath);

		struct stat statbuf;
		if (stat(fullpath, &statbuf) == 0 && S_ISDIR(statbuf.st_mode)){
			list_dir(fullpath);
		}
	}
	closedir(dp);
}

int main(){
	list_dir(".");
	return 0;
}



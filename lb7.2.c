#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <string.h>

void print_permissions(mode_t mode){
	if (S_ISREG(mode)) printf("-");
	else if (S_ISDIR(mode)) printf("d");
	else if (S_ISLNK(mode)) printf("l");
	else if (S_ISCHR(mode)) printf("c");
	else if (S_ISBLK(mode)) printf("b");
	else if (S_ISFIFO(mode)) printf("p");
	else if (S_ISSOCK(mode)) printf("s");
	else printf("?");

	printf((mode & S_IRUSR) ? "r" : "-");
	printf((mode & S_IWUSR) ? "w" : "-");
	printf((mode & S_IXUSR) ? "x" : "-");
	printf((mode & S_IRGRP) ? "r" : "-");
	printf((mode & S_IWGRP) ? "w" : "-");
	printf((mode & S_IXGRP) ? "x" : "-");
	printf((mode & S_IROTH) ? "r" : "-");
	printf((mode & S_IWOTH) ? "w" : "-");
	printf((mode & S_IXOTH) ? "x" : "-");
}

int main(){
	DIR *dir;
	struct dirent *entry;
	struct stat file_stat;
	
	dir = opendir(".");
	if (!dir){
		perror("opendir");
		return 1;
	}

	while ((entry = readdir(dir)) != NULL){
		if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
			continue;
	
		if(stat(entry->d_name, &file_stat) == -1){
			perror("stat");
			continue;
		}

		print_permissions(file_stat.st_mode);
		printf(" %ld", (long)file_stat.st_nlink);
	
		struct passwd *pw = getpwuid(file_stat.st_uid);
		struct group *gr = getgrgid(file_stat.st_uid);
	
		printf(" %s", pw ? pw->pw_name :"?");
		printf(" %s", gr ? gr ->gr_name :"?");
		printf(" %5ld", (long)file_stat.st_size);

		char timebuf[80];
		strftime(timebuf, sizeof(timebuf), "%b %d %H:%M", localtime(&file_stat.st_mtime));
		printf(" %s", timebuf);
	
		printf(" %s\n", entry->d_name);
	
	}
	closedir(dir);
	return 0;
}

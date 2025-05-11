#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
	int fd1 = open("/dev/null", O_RDONLY);
	int fd2 = open("example.txt", O_WRONLY | O_CREAT, 0644);

	if (fd1 < 0 || fd2 < 0){
		perror("open");
		exit(EXIT_FAILURE);
	}

	printf("Opened file descriptors (simulated):\n");
	printf("FD %d -> /dev/null\n",fd1);
	printf("FD %d -> example.txt\n",fd2);

	sleep(10);
	
	close(fd1);
	close(fd2);
	return 0;
}

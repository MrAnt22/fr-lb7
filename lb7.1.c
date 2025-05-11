#include <stdio.h>
#include <stdlib.h>

int main(){
	FILE *rwho_pipe;
	char command[256];

	snprintf(command, sizeof(command), "ls -la /etc | more");

	rwho_pipe = popen(command, "r");

	if (rwho_pipe == NULL){
		perror("open");
		return 1;
	}

	char buffer[256];
	while (fgets(buffer, sizeof(buffer), rwho_pipe) != NULL){
		fputs(buffer, stdout);
	}
	
	int status = pclose(rwho_pipe);
	printf("\n [Process exited with status %d]\n", status);

	return 0;
}




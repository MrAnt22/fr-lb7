#include <stdio.h>
#include <time.h>

long time_diff_ms(struct timespec start, struct timespec end){
	long seconds = end.tv_sec - start.tv_sec;
	long nanoseconds = end.tv_nsec - start.tv_nsec;
	
	if(nanoseconds < 0){
		seconds -= 1;
		nanoseconds += 1000000000;
	}
	return seconds * 1000 + nanoseconds / 1000000;
}

int main(){
	struct timespec start, end;

	clock_gettime(CLOCK_MONOTONIC, &start);

	volatile long sum = 0;
	for (long i = 0;i < 100000000;i++){
		sum += i;
	}

	clock_gettime(CLOCK_MONOTONIC, &end);
	
	long elapsed_ms = time_diff_ms(start, end);
	printf("Elapsed time: %ld ms\n", elapsed_ms);

	return 0;
}


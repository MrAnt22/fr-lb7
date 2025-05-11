#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float random_0_to_1(){
	return (float)rand() / (float)RAND_MAX;
}

float random_0_to_n(float n){
	return random_0_to_1() *n;
}

int main(){
	srand((unsigned int)time(NULL));

	int count = 10;
	float n = 5.0;

	printf("Rand num[0.0, 1.0]:\n");
	for (int i = 0;i < count;++i){
		printf("%.6f\n",random_0_to_1());
	}

	printf("\n Random num[0.0, %.2f]:\n",n);
	for (int i = 0;i < count;++i){
		printf("%.6f\n",random_0_to_n(n));
	}
	return 0;
}


#include <omp.h>
#include <stdio.h>


int main()
{
	omp_set_num_threads(4);

// preprocessor's params acquire higher priority
#pragma omp parallel num_threads(2)
	{
		printf("Hello World!\n");
	}

	getchar();
	return 0;
}
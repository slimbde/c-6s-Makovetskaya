#include <stdio.h>
#include <omp.h>
#include <thread>


int main(int argc, char* argv[])
{
	// argv[1] is set to 5

	if(argc < 2)
	{
		printf("too few arguments..");
		return -1;
	}

	int k = atoi(argv[1]);

#pragma omp parallel num_threads(k)
	{
		int ompnumthreads = omp_get_num_threads();
		int ompthreadnum = omp_get_thread_num();

		printf("I am %d thread of %d threads! My windows threadid is %d\n", ompthreadnum, ompnumthreads, _threadid);
	}
	printf("\n");

#pragma omp parallel num_threads(k)
	{
		int threadid = omp_get_thread_num();
		if(threadid % 2 == 0)
			printf("I am %d thread of %d threads!\n", threadid, omp_get_num_threads());
	}
	printf("\n");


	getchar();
	return 0;
}
#include <stdio.h>
#include <omp.h>
#include <chrono>


int main(void)
{
	typedef unsigned __int64 ullint;
	typedef __int64 llint;

	llint N = 0;

	while(!(N < UINT32_MAX) || N <= 0)
	{
		printf("define N as positive integer: ");
		scanf_s("%lld", &N, 1);

		if(!(N < UINT32_MAX) || N < 0)
		{
			printf("Too huge number! Max uint is %I32u\n\n", UINT32_MAX);
			continue;
		}

		printf("N = %I64d\n\n", N);
	}

	int nthreads;
	printf("define threads num for number handling: ");
	scanf_s("%d", &nthreads, 1);
	printf("\n");
	fflush(stdin);

	ullint summ = 0;
	ullint localsumm = 0;

	auto start = std::chrono::steady_clock::now();

#pragma omp parallel num_threads(nthreads) firstprivate(localsumm)
	{
#pragma omp for reduction(+: summ) schedule(dynamic)
		for(llint i = 0; i <= N; ++i)
		{
			summ += i;
			localsumm += i;
			printf("[%d]: calculation of the iteration #%I64d\n", omp_get_thread_num(), i);
		}
		printf("[%d]: Sum = %I64u\n", omp_get_thread_num(), localsumm);
	}

	auto end = std::chrono::steady_clock::now();
	printf("Sum = %I64u\n\n", summ);

	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	printf("calculation took: %I64d ms.\n", duration);

	getchar();
	return 0;
}
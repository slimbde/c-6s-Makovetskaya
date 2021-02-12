#include <stdio.h>
#include <omp.h>
#include <chrono>
#include <limits.h>


int main(void)
{
	typedef unsigned __int64 ullint;

	int N = 0;
	ullint summ = 0;

	while(!(N < INT32_MAX) || N <= 0)
	{
		printf("define N: ");
		char buf[255] = { 0 };

		scanf_s("%s", buf, sizeof(buf));
		N = atoi(buf);

		if(!(N < INT32_MAX) || N < 0)
		{
			printf("Too huge number! Max int is %d\n\n", INT32_MAX);
			continue;
		}

		printf("N = %I32d\n\n", N);
	}

	auto start = std::chrono::steady_clock::now();
#pragma omp parallel num_threads(2) reduction(+: summ)
	{
		if(omp_get_thread_num() == 0)
		{
			for(int i = 1; i <= N / 2; ++i)
				summ += i;
		}
		else if(omp_get_thread_num() == 1)
		{
			for(int i = N / 2 + 1; i <= N; ++i)
				summ += i;
		}

		printf("[%d]: Sum = %lld\n", omp_get_thread_num(), summ);
	}
	printf("Sum = %lld\n\n", summ);
	auto end = std::chrono::steady_clock::now();

	__int64 duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	printf("calculation took: %lld ms.\n\n", duration);


	summ = 0;
	int nthreads;
	printf("now define threads num for the same number: ");
	scanf_s("%d", &nthreads, 1);
	fflush(stdin);

	start = std::chrono::steady_clock::now();
#pragma omp parallel num_threads(nthreads) reduction(+: summ)
	{
		const int delta = N / nthreads + 1;
		const int offset = omp_get_thread_num()*delta;

		for(int i = offset; (i < offset + delta) && (i <= N); ++i)
			summ += i;

		printf("[%d]: Sum = %lld\n", omp_get_thread_num(), summ);
	}
	printf("Sum = %lld\n\n", summ);
	end = std::chrono::steady_clock::now();

	duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	printf("calculation took: %lld ms.\n", duration);

	getchar();
	return 0;
}
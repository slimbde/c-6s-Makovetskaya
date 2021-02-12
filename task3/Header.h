#pragma once
#include <stdio.h>
#include <omp.h>


void parallel_cycle()
{
	int sum = 0;

	for(int i = 0; i < 20; ++i)
		sum += i;

	printf("sum seq = %d\n", sum);

	sum = 0;
#pragma omp parallel for reduction(+:sum)
	for(int i = 0; i < 20; ++i)
		sum += i;

	printf("sum parallel = %d\n", sum);
}
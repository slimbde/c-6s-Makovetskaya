#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <memory.h>


int main(void)
{
	typedef __int64 llint;

	const int buflength = 255;
	char* buf = (char*)malloc(buflength);

	printf("define precision N: ");
	scanf_s("%s", buf, buflength);
	fflush(stdin);

	llint N = _atoi64(buf);
	int nthreads;

	printf("define threads num for handling: ");
	scanf_s("%d", &nthreads, 1);
	printf("\n");
	fflush(stdin);

	double Pi = 0.0;

#pragma omp parallel num_threads(nthreads) shared(Pi)
	{
		double Xi = .5 / N;

#pragma omp for reduction(+: Pi) schedule(guided)
		for(llint i = 0; i < N; ++i)
		{
			Pi += 4. / (1 + Xi*Xi);
			Xi = ((double)i + .5) / N;
		}
	}

	_i64toa_s((llint)Pi, buf, buflength, 10);

	buf = _strrev(buf);

	int length = strlen(buf);
	buf[length - 1] = '.';
	buf[length] = '3';
	buf[length + 1] = '\0';
	buf = _strrev(buf);

	printf("Pi = %s\n", buf);

	free(buf);

	getchar();
	return 0;
}
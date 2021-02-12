#include <stdio.h>
#include <windows.h>
#include <omp.h>


int main(int argc, char* argv[])
{
	// argv[1] is set to 10

	if(argc < 2)
	{
		printf("too few arguments..");
		getchar();
		return -1;
	}

	int k = atoi(argv[1]);
	int rank;

	printf("shared 'rank'\n");
#pragma omp parallel shared(rank) num_threads(k)
	{
		rank = omp_get_thread_num();
		Sleep(100);
		// инициализация переменной пройдет по очереди
		// значение ее останется тем, которое установил последний поток
		// после паузы 100мс на экран попадет значение от последнего потока
		printf("I am %d thread.\n", rank);
	}

	printf("\nprivate 'rank'\n");
#pragma omp parallel private(rank) num_threads(k)
	{
		rank = omp_get_thread_num();
		Sleep(100);
		// тут переменная у каждого своя
		// поэтому никто другой ее изменить не может
		printf("I am %d thread.\n", rank);
	}

	////////////////////////////////////// lock
	omp_lock_t writelock;

	omp_init_lock(&writelock);

#pragma omp parallel num_threads(k)
	{
		// установка блокировки
		omp_set_lock(&writelock);

		rank = omp_get_thread_num();

		// удаление блокировки
		omp_unset_lock(&writelock);
	}

	omp_destroy_lock(&writelock);

	getchar();
	return 0;
}
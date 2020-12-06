#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#define MAX 50
sem_t full, empty;
pthread_mutex_t mutex;
//Global variables
int count = 0, in = 0, out = 0, a[5];
//Display buffer contents
void show_buffer_contents()
{
	printf("\n CONTENTS OF THE BUFFER :");
	if (in == out && a[in] != -1)
	{
		for (int i = in, j = 0; j < 5; i++, j++)
		{
			if (i > 4)

				i = 0;
			printf("%d ", a[i]);
		}
	}
	for (int i = out; i != in; i++)
	{
		if (i > 4)
		{
			if (in == 0)
				break;
			i = 0;
		}
		if (a[i] != -1)
			printf("%d ", a[i]);
	}
	printf("\n");
}
void *producer(void *arg)
{
	int i = (int *)arg;
	while (1)
	{
		sem_wait(&empty);
		pthread_mutex_lock(&mutex);
		if (count >= 5)
			printf("\n !!!- BUFFER IS FULL -!!!");
		else
		{
			a[in] = rand() % 20;
			printf("\nPRODUCER %d PRODUCED THE ITEM : %d", i, a[in]);

			in = (in + 1) % 5;
			count++;
			show_buffer_contents();
		}
		pthread_mutex_unlock(&mutex);
		sem_post(&full);
		sleep(1);
	}
	pthread_exit(0);
}
void *consumer(void *arg)
{
	int i = (int *)arg;
	while (1)
	{
		sem_wait(&full);
		pthread_mutex_lock(&mutex);
		if (count <= 0)
			printf("\n !!!- BUFFER IS EMPTY -!!!");
		else
		{
			printf("\nCONSUMER %d CONSUMED THE ITEM: %d", i, a[out]);

			a[out] = -1;
			out = (out + 1) % 5;
			count--;
			show_buffer_contents();
		}
		pthread_mutex_unlock(&mutex);
		sem_post(&empty);
		sleep(rand() % 4);
	}

	pthread_exit(0);
}
int main()
{
	for (int i = 0; i < 5; i++)
		a[i] = -1;
	int i, n_producers, n_consumers;
	pthread_t prod[MAX], cons[MAX];
	pthread_mutex_init(&mutex, NULL);
	sem_init(&full, 0, 0);
	sem_init(&empty, 0, 5);
	printf("\nENTER THE NUMBER OF THE PRODUCERS AND CONSUMERS ");
	scanf("%d%d", &n_producers, &n_consumers);
	for (i = 1; i <= n_producers; i++)
		pthread_create(&prod[i], NULL, producer, (void *)i);
	for (i = 1; i <= n_consumers; i++)
		pthread_create(&cons[i], NULL, consumer, (void *)i);
	for (i = 1; i <= n_producers; i++)
		pthread_join(prod[i], NULL);
	for (i = 1; i <= n_consumers; i++)
		pthread_join(cons[i], NULL);
	pthread_mutex_destroy(&mutex);
	sem_destroy(&full);
	sem_destroy(&empty);
	return 0;
}
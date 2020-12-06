
#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#define N 5

sem_t mutex; 
sem_t S[N];

void *philospher(void *num);
void forkUp(int);
void forkDown(int);

int state[N];
int phil_num[N]={0,1,2,3,4};

int main() {
    int i;
    pthread_t thread_id[N];
    
    for(i=0;i<N;i++)
    	sem_init(&S[i],0,1);
    	
    for(i=0;i<N;i++) {
        pthread_create(&thread_id[i],NULL,philospher,&phil_num[i]);
        printf("Philosopher %d is now thinking \n",i+1);
    }
    for(i=0;i<N;i++)
        pthread_join(thread_id[i],NULL);
}

void *philospher(void *num) {
    while(1)
    {
        int *i = num;
        sleep(1);
        forkUp(*i);
	printf("Philisopher %d is eating\n", (*i)+1);
	sleep(1); 
        forkDown(*i);
    }
}

void forkUp(int ph_num) {
	int LEFT = ph_num; 
	int RIGHT = (ph_num+1)%N; 
	
	if (ph_num==N-1) {
		sem_wait(&S[RIGHT]); 
		printf("Philisopher %d picked the fork %d Up\n", (ph_num)+1, RIGHT);
		sem_wait(&S[LEFT]); 
		printf("Philisopher %d picked the fork %d Up\n", (ph_num)+1, LEFT);	
	} else {
		sem_wait(&S[LEFT]); 
		printf("Philisopher %d picked the fork %d Up\n", (ph_num)+1, LEFT);
		sem_wait(&S[RIGHT]); 
		printf("Philisopher %d picked the fork %d Up\n", (ph_num)+1, RIGHT);	
	}
}

void forkDown(int ph_num) {
	int LEFT = ph_num; 
	int RIGHT = (ph_num+1)%N; 

	sem_post(&S[LEFT]); 
	printf("Philisopher %d put the fork %d down\n", (ph_num)+1, LEFT);
	sem_post(&S[RIGHT]); 
	printf("Philisopher %d put the fork %d down \n", (ph_num)+1, RIGHT);
}
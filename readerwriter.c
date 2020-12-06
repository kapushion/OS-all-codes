#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

sem_t mutex,writeblock;
int data = 0,rcount = 0;

int random() {

}

void *reader(void *arg)
{
  int f;
  f = ((int)arg);
  sem_wait(&mutex);
  rcount = rcount + 1;
  if(rcount==1)
   sem_wait(&writeblock);
  sem_post(&mutex);
  printf("Data read by the reader %d is %d\n",f,data);
  sleep(1);
  sem_wait(&mutex);
  rcount = rcount - 1;
  if(rcount==0)
   sem_post(&writeblock);
  sem_post(&mutex);
}

void *writer(void *arg)
{
  int f;
  f = ((int) arg);
  sem_wait(&writeblock);
  data++;
  printf("Data writen by the writer %d is %d\n",f,data);
  sleep(1);
  sem_post(&writeblock);
}

int main()
{
  int i,b; 
  pthread_t read[10],write[10];
  sem_init(&mutex,0,1);
  sem_init(&writeblock,0,1);
  int n,m;
  printf("Enter the no of writer thread: ");
  scanf("%d",&n);
  printf("Enter the no of reader thread: ");
  scanf("%d",&m);
  for(i=0;i<=m;i++)
  {
    pthread_create(&read[i],NULL,reader,(void *)i);
  }
  for(i=0;i<=n;i++) {
    pthread_create(&write[i],NULL,writer,(void *)i);
  }
  for(i=0;i<=m;i++)
  {

    pthread_join(read[i],NULL);
  }
  for(i=0;i<=n;i++) {
      pthread_join(write[i],NULL);
  }
  return 0;
}
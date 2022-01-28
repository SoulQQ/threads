#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include<pthread.h>
#include<semaphore.h>

struct Node
{
	int num;
	struct Node * next;
};

struct Node* head = NULL;

pthread_mutex_t mutex;

sem_t psem;
sem_t csem;

void * productor(void * arg)
{
	while(1)
	{
		sem_wait(&psem);
		struct Node * new= (struct Node*)malloc(sizeof(struct Node));
		new->num=rand()%1000;
		new->next=head;
		head=new;
		printf("productor num = %d, tid = ld%\n",new->num,pthread_self());
		sem_post(&csem);
		sleep(rand()%3);
	}
	return NULL;
}


void * consumer(void * arg)
{
	while(1)
	{
		sem_wait(&csem);
		struct Node * new= head;
		printf("consumer num = %d, tid = ld%\n",new->num,pthread_self());
		head=new->next;
		free(new);
		sem_post(&psem);
		sleep(rand()%3);
	}
	return NULL;
}
int main()
{
	sem_init(&psem,0,1);
	sem_init(&csem,0,0);
	pthread_t ptid[5];
	pthread_t ctid[5];

	for(int i=0;i<5;i++)
	{
		pthread_create(&ptid[i],NULL,productor,NULL);	
	}
	for(int i=0;i<5;i++)
	{
		pthread_create(&ctid[i],NULL,consumer,NULL);	
	}

	
	for(int i=0;i<5;i++)
	{
		pthread_join(ptid[i],NULL);	
	}
	for(int i=0;i<5;i++)
	{
		pthread_join(ctid[i],NULL);	
	}
	
//	sem_destory(&psem);
//	sem_destory(&csem);

	return 0 ;
}

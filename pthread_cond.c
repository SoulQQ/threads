#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include<pthread.h>

struct Node
{
	int num;
	struct Node * next;
};

struct Node* head = NULL;

pthread_mutex_t mutex;

pthread_cond_t cond;

void * productor(void * arg)
{
	while(1)
	{
		pthread_mutex_lock(&mutex);
		struct Node * new= (struct Node*)malloc(sizeof(struct Node));
		new->num=rand()%1000;
		new->next=head;
		head=new;
		printf("productor num = %d, tid = ld%\n",new->num,pthread_self());
		pthread_mutex_unlock(&mutex);

		pthread_cond_broadcast(&cond);

		sleep(rand()%3);
	}
	return NULL;
}


void * consumer(void * arg)
{
	while(1)
	{
		pthread_mutex_lock(&mutex);
		while(head==NULL)
		{
			pthread_cond_wait(&cond,&mutex);
		}
		struct Node * new= head;
		printf("consumer num = %d, tid = ld%\n",new->num,pthread_self());
		head=new->next;
		free(new);
		pthread_mutex_unlock(&mutex);

		sleep(rand()%3);
	}
	return NULL;
}
int main()
{
	pthread_cond_init(&cond,NULL);

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
//	pthread_cond_destory(&cond);
//	pthread_mutex_destory(&mutex);
	return 0 ;
}

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>

int num=0;

pthread_rwlock_t rwlock;

void * writeNum(void *arg)
{
	while(1){
		pthread_rwlock_wrlock(&rwlock);
		int cur=num;
		cur++;
		num=cur;
		printf("Write  num = %d, tid = %ld\n",num,pthread_self());
		pthread_rwlock_unlock(&rwlock);
		usleep(rand()%100);
	}
	return NULL;
}

void * readNum(void *arg)
{
	while(1){
		pthread_rwlock_rdlock(&rwlock);
		printf("Read  num = %d, tid = %ld\n",num,pthread_self());
		pthread_rwlock_unlock(&rwlock);
		usleep(rand()%100);
	}

	return NULL;
}

int main()
{
	pthread_rwlock_init(&rwlock,NULL);

	pthread_t wtid[3];
	pthread_t rtid[5];
	
	for(int i=0;i<3;i++)
	{
		pthread_create(&wtid[i],NULL,writeNum,NULL);
	}
	for(int i=0;i<5;i++)
	{
		pthread_create(&rtid[i],NULL,readNum,NULL);
	}

	for(int i=0;i<3;i++)
	{
		pthread_join(wtid[i],NULL);
	}

	for(int i=0;i<5;i++)
	{
		pthread_join(rtid[i],NULL);
	}

//	pthread_rwlock_destory(&rwlock);
	
	return 0;
}

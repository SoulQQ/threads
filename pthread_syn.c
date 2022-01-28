#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include<pthread.h>

#define MAX  50


int num;

void * fun_A(void *arg)
{
	for(int i=0;i<MAX;i++)
	{
		int cur=num;
		cur++;
		usleep(10);
		num=cur;
		printf("Thread A id = %lu, number =%d\n",pthread_self(),num);
	}

	return NULL;
 }



void * fun_B(void *arg)
{
	for(int i=0;i<MAX;i++)
	{
		int cur=num;
		cur++;
		num=cur;
		printf("Thread A id = %lu, number =%d\n",pthread_self(),num);
		usleep(5);
	}

	return NULL;
 }

int main()
{
	pthread_t p1,p2;

	pthread_create(&p1,NULL,fun_A,NULL);
	pthread_create(&p2,NULL,fun_B,NULL);

	pthread_join(p1,NULL);
	pthread_join(p2,NULL);


	return 0;
}

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>

void * callback(void *arg)
{
	printf("zi : %ld\n",pthread_self());
	
	for(int i=0;i<5;i++)
	{
		printf("zi   i= %d \n",i);
	}
	return NULL;

}


int main()
{
	pthread_t tid;
	pthread_create(&tid,NULL,*callback,NULL);

	printf("zhu %ld", pthread_self());

	for(int i=0;i<5;i++)
	{
		printf("zhu  i= %d \n",i);
	}
	pthread_exit(NULL);
//	sleep(2);
	return 0;
}

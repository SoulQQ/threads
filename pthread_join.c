#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>

struct test 
{
	int num;
	int age;
};

void * callback(void *arg)
{
	printf("zi : %ld\n",pthread_self());
	
	for(int i=0;i<5;i++)
	{
		printf("zi   i= %d \n",i);
	}
	struct test *t =(struct test*)arg;
	t->num=10;
	t->age=5;

	pthread_exit(t);//take the para back to main thread

	return NULL;

}


int main()
{
	pthread_t tid;
	struct test t;
	pthread_create(&tid,NULL,*callback,&t);

	printf("zhu %ld", pthread_self());

	for(int i=0;i<5;i++)
	{
		printf("zhu  i= %d \n",i);
	}
	void * ptr;// son thread "exit &t" cover *ptr
	
	pthread_join(tid,&ptr); //wait son thread fineshed
	printf("num is : %d, age is :%d\n",t.num,t.age);
	return 0;
}

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>


int mails = 0;
pthread_mutex_t mutex;


void *routine()
{
	for (int i = 0; i < 1000000; i++) {
		pthread_mutex_lock(&mutex);
	    mails++;
	    pthread_mutex_unlock(&mutex);
	}

	printf("start test from threads\n");
	sleep(1);
	printf("end test from threads\n");
}


int main(int arg, char *argv[])
{
    pthread_t t[4];

    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < 4; i++) {
    	if (0 != pthread_create(&t[i], NULL, &routine, NULL)) {
    		 exit(-1);
    	}
    }
    
    for (int i = 0; i < 4; i++) {
    	if (0 != pthread_join(t[i], NULL)) {
         exit(-1);
        }
    }

    pthread_mutex_destroy(&mutex);

    printf("%d\n\n", mails);

	exit(0);
}
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

/*******************************************
 *  pthread_cancel  
********************************************/

void *thread_function(void *arg);

int main(int argc, char *argv[])
{
    int res;
    pthread_t a_thread;
    void *thread_result;

    // Create Thread
    res = pthread_create(&a_thread, NULL, thread_function, NULL);
    if (res != 0)
    {
        perror("Thread create failed");
        exit(EXIT_FAILURE);
    }

    sleep(3);
    printf("canceling thread..\n");

    // cancel
    res = pthread_cancel(a_thread);
    if (res != 0)
    {
        perror("Thread cancelation failed");
        exit(EXIT_FAILURE);
    }

    printf("Wait for thraed to finished...\n");
    res = pthread_join(a_thread, &thread_result);
    if (res != 0)
    {
        perror("Thread join failed");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}

void *thread_function(void *arg)
{
    int i, res;

    res = pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL); // ??????
    if (res != 0)
    {
        perror("Thread pthread_setcancelstate failed");
        exit(EXIT_FAILURE);
    }

    // PTHREAD_CANCEL_DEFERRED???????? join?wait ?????
    res = pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);
    if (res != 0)
    {
        perror("Thread pthread_setcanceltype failed");
        exit(EXIT_FAILURE);
    }

    printf("thread_function is running\n");
    for (i = 0; i < 10; ++i)
    {
        printf("thread is still running [%d]\n", i);
        sleep(1);
    }

    pthread_exit(NULL);
}

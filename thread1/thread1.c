#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

/********************
 *  thread
***********************/

/*
OutPut:

Wait for thraed to finished...
thread_function is running. arg was: hello world
Thread joined, it returned: Thank you for the cpu time. 
Message is now: bye !
*/

void *thread_function(void *arg);
char message[] = "hello world";

int main(int argc, char *argv[])
{
    int res;
    pthread_t a_thread;
    void *thread_result;

    // Create Thread
    res = pthread_create(&a_thread, NULL, thread_function, (void *)message);
    if (res != 0)
    {
        perror("Thread create failed");
        exit(EXIT_FAILURE);
    }

    printf("Wait for thraed to finished...\n");

    // Main thread wait for termination of a_thread.
    // thread_result： a_thread return
    res = pthread_join(a_thread, &thread_result);
    if (res != 0)
    {
        perror("Thread join failed");
        exit(EXIT_FAILURE);
    }

    printf("Thread joined, it returned: %s\n", (char *)thread_result);
    printf("Message is now: %s\n", message);
    exit(EXIT_SUCCESS);
}

void *thread_function(void *arg)
{
    printf("thread_function is running. arg was: %s\n", (char *)arg);
    sleep(3);
    strcpy(message, "bye !");
    pthread_exit("Thank you for the cpu time. ");
}

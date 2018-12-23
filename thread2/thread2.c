#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>

/********************
 *  semaphore
***********************/

void *thread_function(void *arg);
sem_t bin_sem;

#define work_size 1024
char work_area[work_size];

int main(int argc, char *argv[])
{
    int res;
    pthread_t a_thread;
    void *thread_result;

    // semaphore init
    res = sem_init(&bin_sem, 0, 0);
    if (res != 0)
    {
        perror("semaphore initialization failed");
        exit(EXIT_FAILURE);
    }

    // Create Thread
    res = pthread_create(&a_thread, NULL, thread_function, NULL);
    if (res != 0)
    {
        perror("Thread create failed");
        exit(EXIT_FAILURE);
    }

    printf("Input some text. Enter 'end' to finish.\n");
    while (strncmp("end", work_area, 3) != 0)
    {
        fgets(work_area, work_size, stdin);
        sem_post(&bin_sem); // 信号量 + 1
    }

    printf("\nWait for thraed to finished...\n");
    res = pthread_join(a_thread, &thread_result);
    if (res != 0)
    {
        perror("Thread join failed");
        exit(EXIT_FAILURE);
    }

    printf("Thread joined\n");
    sem_destroy(&bin_sem);
    exit(EXIT_SUCCESS);
}

void *thread_function(void *arg)
{
    sem_wait(&bin_sem); // 信号量初始值为 0，线程等待输入，大于 0 才进行 - 1 操作
    while (strncmp("end", work_area, 3) != 0)
    {
        printf("You input %d characters\n", strlen(work_area) - 1);
        sem_wait(&bin_sem);
    }
    pthread_exit(NULL);
}

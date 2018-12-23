#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

/*************************************
 *  condition variables
************************************/

#define CONSUMERS_COUNT 1
#define PRODUCERS_COUNT 4

#define PRODUCTS_NUMBER 6 // 商品缓存最多 6 件

pthread_mutex_t g_mutex;

// two condition variables
pthread_cond_t g_cond_empty;
pthread_cond_t g_cond_full;

int nready = 0; // 当前产品个数

void *consumer_function(void *arg); 

void *producer_function(void *arg);

int main(int argc, char *argv[])
{
    int res;
    pthread_t a_thread[CONSUMERS_COUNT + PRODUCERS_COUNT];
    void *thread_result;
    int lots_of_threads;

    // mutex init
    res = pthread_mutex_init(&g_mutex, NULL);
    if (res != 0)
    {
        perror("Mutex create failed\n");
        exit(EXIT_FAILURE);
    }

    // condition variables init
    res = pthread_cond_init(&g_cond_empty, NULL);
    if (res != 0)
    {
        perror("condition variables create failed\n");
        exit(EXIT_FAILURE);
    }

    res = pthread_cond_init(&g_cond_full, NULL);
    if (res != 0)
    {
        perror("condition variables create failed\n");
        exit(EXIT_FAILURE);
    }

    // create consumer
    for (lots_of_threads = 0; lots_of_threads < CONSUMERS_COUNT; ++lots_of_threads)
    {
        res = pthread_create(&a_thread[lots_of_threads], NULL, consumer_function, (void *)&lots_of_threads);
        if (res != 0)
        {
            perror("Thread create failed\n");
            exit(EXIT_FAILURE);
        }

        sleep(1);
    }

    // create producer
    for (lots_of_threads = 0; lots_of_threads < PRODUCERS_COUNT; ++lots_of_threads)
    {
        res = pthread_create(&a_thread[lots_of_threads + CONSUMERS_COUNT], NULL, producer_function, (void *)&lots_of_threads);
        if (res != 0)
        {
            perror("Thread create failed\n");
            exit(EXIT_FAILURE);
        }
        sleep(1);
    }

    printf("Wait for thraed to finished...\n");
    for (lots_of_threads = CONSUMERS_COUNT + PRODUCERS_COUNT - 1; lots_of_threads >= 0; --lots_of_threads)
    {
        res = pthread_join(a_thread[lots_of_threads], &thread_result);

        if (res == 0)
        {
            printf("pick up a thread\n");
        }
        else
        {
            perror("Thread join failed\n");
        }
    }

    pthread_cond_destroy(&g_cond_empty);
    pthread_cond_destroy(&g_cond_full);
    pthread_mutex_destroy(&g_mutex);

    printf("All done\n");
    exit(EXIT_SUCCESS);
}

void *consumer_function(void *arg)
{
    int i = *(int *)arg;
    while (1)
    {
        pthread_mutex_lock(&g_mutex);
        while (nready == 0)
        {
            printf("Consumers Wait product [%d][%d]\n", i, nready);
            pthread_cond_wait(&g_cond_empty, &g_mutex); // 挂在空的条件变量
        }

        --nready;
        printf("Consumers consumed product [%d]\n", i);
        pthread_cond_signal(&g_cond_full); // 通知挂在满条件变量上的线程
        pthread_mutex_unlock(&g_mutex);

        sleep(1);
    }

    pthread_exit(NULL);
}

void *producer_function(void *arg)
{
    int i = *(int *)arg;
    while (1)
    {
        pthread_mutex_lock(&g_mutex);
        while (nready == PRODUCTS_NUMBER) // while 可能虚假唤醒，需要重新检测一下
        {
            printf("producer Wait consume [%d][%d]\n", i, nready);
            pthread_cond_wait(&g_cond_full, &g_mutex); // 挂在满的条件变量
        }

        ++nready;
        printf("producer produced a product [%d]\n", i);
        pthread_cond_signal(&g_cond_empty);
        pthread_mutex_unlock(&g_mutex);

        sleep(1);
    }
    pthread_exit(NULL);
}

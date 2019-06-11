#include "stdio.h"
#include "pthread.h"

/***************************************************
 *  Read-write lock
 * 
 *  API
 *    初始化读写锁的函数：int pthread_rwlock_init(pthread_rwlock_t *restrict rwlock, 
 *                                                  const pthread_rwlockattr_t *restrict attr);
 *    回收读写锁函数： int pthread_rwlock_destroy(pthread_rwlock_t *rwlock);
 *    读模式加锁函数： int pthread_rwlock_rdlock(pthread_rwlock_t *rwlock);
 *    写模式加锁函数： int pthread_rwlock_wrlock(pthread_rwlock_t *rwlock);
 *    解锁函数：int pthread_rwlock_unlock(pthread_rwlock_t *rwlock);
 * 
 *    非阻塞加锁函数：
 *    int pthread_rwlock_tryrdlock(pthread_rwlock_t *rwlock);
 *    int pthread_rwlock_trywrlock(pthread_rwlock_t *rwlock);
 * 
 *    带有超时的读写锁函数：
 *    int pthread_rwlock_timedrdlock(pthread_rwlock_t *restrict rwlock,
 *                                        const struct timespec *restrict abs_timeout);
 *    int pthread_rwlock_timedwrlock(pthread_rwlock_t *restrict rwlock,
 *                                        const struct timespec *restrict abs_timeout);
 * 
 *  Link： https://www.jianshu.com/p/d9c8bbfefabe
 * 
 *  代码示例: 模拟抢票场景，查询使用读锁，购票采用写锁
 *  程序 thread9 中，有 100 个线程，其中 90 个线程是查余票数量的，只有 10 个线程抢票，每个线程一次买 10 张票。
 *  初始状态下一共有 1000 张票。因此执行完毕后，还会剩下 900 张票。
 *  程序 thread9 在运行的时候需要传入参数，即 ./thread9 <0|1|2>:
 *  参数 0：表示不加任何锁
 *  参数 1：表示使用读写锁
 *  参数 2：表示使用互斥量
 * 
*********************************************************************/

//结构体设置方便对比读写锁与互斥锁
struct Ticket
{
    int remain; //余票数
    pthread_rwlock_t rwlock; //读写锁
    pthread_mutex_t mlock; //互斥锁
}ticket;

int lock = 0;

//查询票的线程
void* query(void* arg) 
{
    int name = (int)arg;
    sleep(rand() % 5 + 1);
    if (lock == 1)
    {
        pthread_rwlock_rdlock(&ticket.rwlock); //读模式加锁
    }
    else if (lock == 2)
    {
        pthread_mutex_lock(&ticket.mlock);
    }

    int remain = ticket.remain;
    sleep(1);
    printf("%03d query: %d\n", name, remain);
    
    if(lock == 1)
    {
        pthread_rwlock_unlock(&ticket.rwlock);
    }
    else if(lock == 2)
    {
        pthread_mutex_unlock(&ticket.mlock);
    }
    return NULL;
}

//抢票的线程
void* buy(void* arg) 
{
    int name = (int)arg;
    
    if(lock == 1)
    {
        pthread_rwlock_wrlock(&ticket.rwlock);//写模式加锁
    }
    else if(lock == 2)
    {
        pthread_mutex_lock(&ticket.mlock);
    }

    int remain = ticket.remain;
    remain -= 10;
    sleep(1);
    ticket.remain = remain;
    printf("%03d buy 10 tickets\n", name);
    
    if(lock == 1)
    {
        pthread_rwlock_unlock(&ticket.rwlock);
    }
    else if(lock == 2)
    {
        pthread_mutex_unlock(&ticket.mlock);
    }

    sleep(rand() % 5 + 2);
    return NULL;
}

int main(int argc, char* argv[]) 
{
    lock = 0;
    if(argc >= 2)
    {
        lock = atoi(argv[1]);
    }
    int names[100];//100个线程名字
    pthread_t tid[100];//100个线程存储数组
    int i;
    
    for (i = 0; i < 100; ++i){
        names[i] = i;
    }
    ticket.remain = 1000; //余票初始为1000张
    
    printf("余票数量 = %d\n", ticket.remain);
    
    pthread_rwlock_init(&ticket.rwlock, NULL);
    pthread_mutex_init(&ticket.mlock, NULL);
    
    for (i = 0; i < 100; ++i) 
    {
        if (i % 10 == 0)
        {
            pthread_create(&tid[i], NULL, buy, (void*)names[i]);
        }
        else
        {
            pthread_create(&tid[i], NULL, query, (void*)names[i]);
        }
    }
    
    for (i = 0; i < 100; ++i) 
    {
        pthread_join(tid[i], NULL);
    }
    
    pthread_rwlock_destroy(&ticket.rwlock);
    pthread_mutex_destroy(&ticket.mlock);
    printf("余票数量 = %d\n", ticket.remain);
    return 0;
}

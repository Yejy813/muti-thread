# **Posix-thread**

## 源码介绍
Posix-thread 简单使用，其中例子基本出自 <<Linux程序设计(第4版)>> , thread8 为自己编写，因为书中无条件变量的使用介绍，thread9 从网上引用。

**1. thread1**
> Posix-thread 简单使用

**2. thread2**
> Posix-thread 的同步属性信号量 semaphore

**3. thread3**
> Posix-thread 的同步属性互斥锁 mutex

**4. thread4**
> pthread_attr_setdetachstate 设置线程分离属性

**5. thread5**
> pthread_attr_setschedparam 设置线程调度属性

**6. thread6**
> pthread_cancel 使用

**7. thread7**
> 创建多个posix-thread线程 

**8. thread8**
> 使用 Posix-thread 条件变量实现生产者消费者

**9. thread9**
> 读写锁使用场景

## 构建
工程构建采用的是 `cmake` ，使用起来很方便!

**1. 创建构建目录 (在源代码目录创建即可)**
> bash-4.2$ mkdir build

**2. 构建指令**
> bash-4.2$ cd build

> bash-4.2$ cmake ..

> bash-4.2$ make install

**3. 执行即可 (可执行文件在：build/output/bin/)**
> bash-4.2$ ./output/bin/thread8







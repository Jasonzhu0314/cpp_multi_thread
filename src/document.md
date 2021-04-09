## 原子操作
情型：<br>
线程1在操作共享数据m时，系统调度切换到线程2，线程2也要操作共享数据m，导致再返回线程1时，共享数据m已经变成另外一个值，影响程序的执行结果
处理共享数据：

共享数据是一个变量时，比如整形变量，两种操作方式
1. 加锁：先加锁，再释放，会影响程序的使用效率，反复的加锁操作，增加程序执行时间
2. 原子操作：需要加锁的代码只有一行，让线程在执行这一行代码时，不会被切换到其他线程

流程
1. 申请原子操作变量`std::atomic<int> g_atomic_count`
2. 在操作共享数据的地方使用，一行代码

注意：
支持++，+=，-=，*=等运算符，其他的可能不支持，比如:`count = count + 1`

## async
### 简介
是一个函数模板，返回值是future类型
一个程序里一般不能超过100~200个线程
std::async函数原型：
```c++
template<class Fn, class... Args>
future<typename result_of<Fn(Args...)>::type> async(launch policy, Fn&& fn, Args&&...args);
```
功能：第二个参数接收一个可调用对象（仿函数、lambda表达式、类成员函数、普通函数......）作为参数,并且异步或是同步执行他们。

### 参数
第一个参数
1. std::launch::deferred，延迟调用，使用get时进行，但是没有创建新的线程
2. std::launch::async，创建新的线程
3. std::launch::async | std::launch::deferred，系统自行决定使用哪一种
4. 如果不适用额外的参数，效果默认为参数类型3，系统自行决定

### 返回值
future:
std::async 会返回一个 std::future 对象，这个对象持有线程最终计算出来的结果。
当你需要这个值时，你只需要调用这个对象的get()成员函数；并且直到“期望”状态为就绪的情况下，线程才会阻塞；之后，返回计算结
果。
```c++
std::future<int> std::async(Mythread);
```

调用函数时不一定会创建线程
只有当future.get的时候，才会去入口函数运行，

和thread的区别
std::thread，当程序的线程过多时，资源紧张，可能导致线程创建失败，thread()时整个程序崩溃
std::thread有可能计算机资源紧张，执行失败，而std::async(std::launch::async, methodName)强制创建一个线程
但是我们一般不叫std::async()创建线程，而是创建一个异步任务，有的时候async并不创建新的线程

## future
### 简介
翻译：期望或者未来


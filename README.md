# cpp_multi_thread

#### 介绍
c++多线程开发

#### 软件架构
软件架构说明

### 多线程基础知识
常用的函数join

#### 线程的创建
包含的头文件`#include <thread>`
thread是一个类
```c++
//myprint 可调用对象，可以是函数，也可以是类变成仿函数。
thread myobj(myprint) 
// （1）当前代码是创建了线程，线程执行的起点(入口) myprint,
// (2) myprint()开始执行
myobj.join() // 阻塞主线程，等待子线程执行完后，再执行
```
可用于生成类的线程对象
- 类的成员函数
```c++
// 在生成对象的过程中，thread中有一个参数是对象本身，因为成员函数本身的函数参数中有一个this指针，指向对象本身，当类的对象调用成员函数时
class A {
public:
    void myprint(const int num)  {};
};
int num = 10;
A a;
std::thread t(&A::myprint, a, 10);
```
- 类的仿函数
```c++
class A {
public:
    void operator()(const int num)  {};
    // ()构造类的仿函数，重载()运算符
};
int num = 10;
A a;
std::thread t(a, 10);
```


- 普通函数
```c++
void myprint(const int num) {  }
std::thread(myprint, 10);
```

#### 线程的控制
1. join
阻塞主线程，等待子线程执行完后，主线程再接着执行 

2. detach
将子线程和主线程分离，分开执行两个线程，但是当主线程执行过快时，会出现子线程没有执行完的情况

3. joinable
调用`join()`的行为，还清理了线程相关的存储部分，这样`std::thread` 对象将不再与已经完成的线程有任何关联。这意味着，只能对一个线程使用一次join();一
旦已经使用过`join()`，`std::thread`对象就不能再次加入了，当对其使用`joinable()`时，将返回否（false）

4. 获取线程id
```c++
std::thread t(hello);
std::thread::id thread_id = t.get_id();	// 获取特定线程的id
std::thread::id this_thread_id = this_thread::get_id(); // 获取本线程的id
```

#### 向线程中传递参数
1. 线程中传递参数的问题
c++11的新版本中，当线程入口函数需要调用参数的时，
- 形参的命名前需要加上const，如果不加const的会报错，就算是使用引用，也会调用拷贝构造函数，子线程中使用类的对象和主线程使用的对象不是同一
- 如果在创建线程是，申请对象时，加上`std::ref`则可以实现调用引用，子线程和主线程一致
```c++
class A {
public:
    void dosomething () { };
    A (int i):m_int(i) { };
    multable int m_int; //const可以修改
};


A a(10);
void change_obj(const A &a) { a.m_int = 10; } 
std::thread t(change_obj, a); // 子线程创建时会调用拷贝构造函数，子线程中修改m_int，不会影响主线程


class A {
public:
    void dosomething () { };
    A (int i):m_int(i) { };
    int m_int; //不使用const，不需要加multable
};

void change_obj(A &a) { a.m_int = 10; } 
std::thread t(change_obj, std::ref(a)); // 子线程创建时不会调用拷贝构造函数，修改m_int，会影响主线程
```
#### 锁与互斥量
当两个线程都要访问进程同一内存时，需要进行加锁处理，防止出现不可预料的情况的发生
mutex作为互斥量变量，在需要对内存访问的代码中进行加锁，防止其他线程再去访问同一线程
```c++
std::mutex mylock;
// 需要进行加锁的代码
mylock.lock();
// do something
mylock.unlock();
```
std::lock_guard() 可以不使用unlock(), 本质上是在他的构造函数中使用了lock()，析构函数中调用了unlock()。
std::lock()可以对多个mutex互斥量进行加锁。

```c++
std::mutex mylock1, mylock2;
std::lock(mylock1, mylock2);
std::lock_guard<mutex> shared_guard1(mylock1, std::adopt_lock())
std::lock_guard<mutex> shared_guard2(mylock2, std::adopt_lock())
```
#### 死锁
当进程中有两个互斥量时，线程A对互斥量A加锁，线程B对互斥量B加锁，导致两个线程都不释放，进程卡死
解决方案：
    1. 当只有对互斥量A和B都能加锁时才执行代码，否则释放互斥量


#### unique_lock类模板
将unique_lock对象mutex绑定在一起
第二个参数：
1. 没有参数，默认会继续加锁
2. std::adopt_lock   // 前面执行了mutex.lock()
3. std::try_to_lock    // 尝试进行加锁，可以调用son_guard.owns_lock()判断是否锁成功
4. std::defer_lock    
只是定义，但是没有执行任何操作，后续可以调用的成员函数进行手动加锁，手动解锁，当操作共享数据时加锁，不操作共享数据时解锁。程序局部返回时可以手动解锁，可以不手动解锁
- try_lock()
- lock()
- unlock()
- release() 返回它管理的mutex对象指针，并释放所有权，也就是说， 这个unique_lock和mutex不再有关系
如果原来的mutex处于加锁状态，要进行接管
std::mutex *ptr = son_guard.release()
```c++
{
    std::unique_lock son_guard(mutex, std::defer_locK);
    son_guard.lock(); // 手动加锁
    // 操作共享数据
    
    son_guard.unlock();
    // 不操作共享数据
    son_gutard.lock()
    // 操作共享数据
    // 程序返回可以执行unlock(),也可以不执行
}
```

#### 锁的粒度
锁头锁住的代码的数量，锁住的代码更少，执行的速度越快，高级程序员


std::chrono
std::this_thread::sleep_for()


#### 安装教程

1.  xxxx
2.  xxxx
3.  xxxx

#### 使用说明

1.  xxxx
2.  xxxx
3.  xxxx

#### 参与贡献

1.  Fork 本仓库
2.  新建 Feat_xxx 分支
3.  提交代码
4.  新建 Pull Request


#### 特技

1.  使用 Readme\_XXX.md 来支持不同的语言，例如 Readme\_en.md, Readme\_zh.md
2.  Gitee 官方博客 [blog.gitee.com](https://blog.gitee.com)
3.  你可以 [https://gitee.com/explore](https://gitee.com/explore) 这个地址来了解 Gitee 上的优秀开源项目
4.  [GVP](https://gitee.com/gvp) 全称是 Gitee 最有价值开源项目，是综合评定出的优秀开源项目
5.  Gitee 官方提供的使用手册 [https://gitee.com/help](https://gitee.com/help)
6.  Gitee 封面人物是一档用来展示 Gitee 会员风采的栏目 [https://gitee.com/gitee-stars/](https://gitee.com/gitee-stars/)

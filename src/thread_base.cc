#include <iostream>
#include <thread>
using namespace std;

void PrintThread() {
    cout << "common function PrintThread "<< endl;
}

class SonThread {
public:
    SonThread() {
        cout << "default constructor func" << endl;
    }
    SonThread(const SonThread &s) {
        cout << "copy constructor func" << endl;
    }
    void operator()() {
        cout << "class functor thread "<< endl;
    }
    void PrintThread() {
        i = 100;
        cout << "class function thread" << endl;
    }
    int i;
};

int main() {
    //创建线程的方式，创建thread对象
    // 1. 普通函数
    thread mythread1(PrintThread);

    mythread1.join(); // 阻塞进程
    // mythread1.detach(); // 子线程和主线程分离
    if (mythread1.joinable()) { // 判断线程是否可以重新加入
        cout << "son thread rejoin" << endl;
        mythread1.join(); // detach和join不能一起使用
    }
    else {
        cout << "son thread can not join" << endl;
    }

    // 2. 类仿函数
    SonThread t;
    thread mythread2(t);
    mythread2.join();
    t.i = 10;
    // 3. 类的成员函数
    thread mythread3(&SonThread::PrintThread, &t);
    mythread3.join();
    cout << t.i << endl;

    return 0;
}
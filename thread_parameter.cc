#include <iostream>
#include <thread>
using namespace std;



void PrintThread(const int& num) {
    cout <<  this_thread::get_id() << ": " << &num << endl;
}

class SonThread {
    void operator()(const int& num) {
        cout <<  this_thread::get_id() << ": " << &num << endl;
    }
};

int main() {
    // 创建线程时传递参数
    // 1. 普通函数
    int num = 10;
    cout << std::this_thread::get_id() << ": " << &num << endl;

    // 不使用std::ref
    thread myobj(PrintThread, num);
    // 使用std::ref，子线程和主线程num地址一样；
    thread myobj1(PrintThread, std::ref(num));

    //myobj.join();
    myobj.detach();
    cout << "son thread detach" << endl;
    cout << &num << endl;
    // myobj.join();
    if (myobj.joinable()) {
        cout << "son thread rejoin" << endl;
        myobj.join();
    }
    else {
        cout << "son thread joinable" << endl;
    }

//    SonThread t;
//    thread myobj2(t);
//    cout << "class son Thread begin" << endl;
//    myobj2.join();
//    cout << "main thread" << endl;

    return 0;
}
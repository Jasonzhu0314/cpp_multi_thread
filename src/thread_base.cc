#include <iostream>
#include <thread>
using namespace std;

//创建线程的方式，创建thread对象时，传入可调用对象
//1. 函数
//2. 类的仿函数
//3. 类的成员函数

void PrintThread(int& num) {
    for (int i = 0; i < 10; i++) {
        cout << "PrintThread func: " << i << endl;
    }
    cout << "endl" << endl;
    num = 100;
    cout << &num << endl;
    cout << this_thread::get_id()<< endl;

}

class SonThread {
    void operator()() {
        for (int i = 0; i < 10; i++) {
            cout << "PrintThread func: " << i << endl;
        }
        cout << "endl" << endl;
    }
};


int main() {
    // 普通函数
    int num = 10;
    thread myobj(PrintThread, ref(num));
    myobj.join();
    //myobj.detach();
    cout << "son thread detach" << endl;
    cout << &num << endl;
    //myobj.join();
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
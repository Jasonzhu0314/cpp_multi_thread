#include <iostream>
#include <thread>
#include <vector>
#include <future>
/*
std::packaged_task 对一个函数或可调用对象，绑定一个期望
1）是个类模板，它的模板类参数是各种可调用对象，通过std::packaged_task来把各种可调用对象包装起来，方便将来作为线程入口函数
2）packaged_task包装起来的可调用对象还可以直接调用，所以从这个角度讲，packaged_task对象，也是一个可调用对象。
std::promise 在某个线程中进行赋值，在其他线程中将这个值取出来

std::vector <std::packaged_task<int(int)> > g_my_tasks;   // 类似于一个容器，将所有的package_task打包到一起，使用迭代器取出
*/

int MyThread() {
    std::chrono::seconds  s_5(5);
//    std::chrono::milliseconds s_5000(5000); // 5000ms
    std::this_thread::sleep_for(s_5);
    return 10;
}


int main() {

//    std::packaged_task <int (int) > my_pack([](int temp) {
//        temp = 10;
//        std::cout << temp << std::endl;
//        return temp;
//    });


    // 1. 单独创建一个线程
    std::future<int> result = std::async(std::launch::async, MyThread);
    // 2. 不单独创建一个线程，当调用wait和get时，线程才开始执行，线程id是主线程id
    // std::future<int> result1 = std::async(std::launch::async | std::launch::deferred, MyThread);
    std::cout << "start" << std::endl;
    // do something
    int a = result.get();
    std::cout << a << std::endl;

    return 0;
}
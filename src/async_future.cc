#include <iostream>
#include <thread>
#include <vector>
#include <future>

/*
 * async:
 * std::thread有可能计算机资源紧张，执行失败，而std::async(std::launch::async, methodName)强制创建一个线程
         但是我们一般不叫std::async()创建线程，而是创建一个异步任务，有的时候async并不创建新的线程
         1）如果用std::launch::deferred，延迟调用，使用get时进行，但是没有创建新的线程
         2）如果用std::launch::async，创建新的线程
         3）如果用std::launch::async | std::launch::deferred，系统自行决定使用哪一种
         4）如果不适用额外的参数，效果默认为3），系统自行决定
         一个程序里一般不能超过100~200个线程
 * future:你可以使用 std::async 启动一个异步任务。与 std::thread 对象等待运行方式的不
    同， std::async 会返回一个 std::future 对象，这个对象持有最终计算出来的结果。当你需要这个值时，你只需
    要调用这个对象的get()成员函数；并且直到“期望”状态为就绪的情况下，线程才会阻塞；之后，返回计算结
    果。下面清单中代码就是一个简单的例子

 * std::packaged_task 对一个函数或可调用对象，绑定一个期望
 *      1）是个类模板，它的模板类参数是各种可调用对象，通过std::packaged_task来把各种可调用对象包装起来，方便将来作为线程入口函数
 *      2）packaged_task包装起来的可调用对象还可以直接调用，所以从这个角度讲，packaged_task对象，也是一个可调用对象。
 *
 * std::promise 在某个线程中进行赋值，在其他线程中将这个值取出来
 */

std::vector <std::packaged_task<int(int)> > g_my_tasks;   // 类似于一个容器，将所有的package_task打包到一起，使用迭代器取出


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
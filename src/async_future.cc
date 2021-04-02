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
 * future:

 * std::packaged_task 打包任务，把任务打包起来
 *      1）是个类模板，它的模板类参数是各种可调用对象，通过std::packaged_task来把各种可调用对象包装起来，方便将来作为线程入口函数
 *      2）packaged_task包装起来的可调用对象还可以直接调用，所以从这个角度讲，packaged_task对象，也是一个可调用对象。
 *
 * std::promise 在某个线程中进行赋值，在其他线程中讲这个值取出来
 */

std::vector <std::packaged_task<int(int)> > g_my_tasks;   // 类似于一个容器，将所有的package_task打包到一起，使用迭代器取出





int main() {

    std::packaged_task <int (int) > my_pack([](int temp) {
        std::cout << temp << std::endl;
        return temp;
    });



    return 0;
}
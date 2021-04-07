#include <iostream>
#include <future>
#include <thread>
#include <chrono>


void MyThread1(std::promise<int> &prom) {
    std::cout << "begin thread 1" << std::endl;
    std::future<int> fut = prom.get_future();
    std::cout << "prom.get_future" << std::endl;
    int a = fut.get(); // 会卡在这里等待prom的set_value
    std::cout << "future get: " << a << std::endl;
}

void MyThread2() {
    for (int i = 0; i < 10 ;i++ ) {
        std::cout << "begin thread 1" << std::endl;
    }
}

int main() {
    std::promise<int> prom;

    std::thread t1(MyThread1, std::ref(prom));
    std::thread t2(MyThread2);

    std::chrono::seconds s(5);
    std::this_thread::sleep_for(s);

    std::cout << "main thread " << std::endl;
    prom.set_value(10); // 主线程中设置某个值，子线程中获取

    t1.join();
    t2.join();
    return 0;
}
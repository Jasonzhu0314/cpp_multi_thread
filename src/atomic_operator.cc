#include <iostream>
#include <future>
#include <thread>

std::mutex m;
int g_count = 0;
// std::atomic<T> 类模板
std::atomic<int> g_atomic_count(0);

void MyThread(){
    for (int i = 0; i < 10000000; i++) {
        // 1.第一种，互斥量加锁，但是不停的加锁解锁，影响速度
        //m.lock();
        //std::lock_guard<std::mutex> lk(m);
        //std::unique_lock<std::mutex> lk1(m);
        g_count++;
        //m.unlock();

        // 2. 使用原子操作
        g_atomic_count++;
    }
}

int main() {

    std::thread my_thread1(MyThread);
    std::thread my_thread2(MyThread);

    my_thread1.join();
    my_thread2.join();

    std::cout << "no atomic operator result: "<< g_count << std::endl;
    std::cout << "atomic operaotr result: " << g_atomic_count << std::endl;
    return 0;
}
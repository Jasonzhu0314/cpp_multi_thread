#include <iostream>
#include <thread>
#include <list>
#include <mutex>

class A {
public:
    void InRecvMessage() {
        for (int i = 0; i < 10000; i++) {
            std::cout << "put command in list" << i << std::endl;
            my_mutex2_.lock();
            my_mutex1_.lock(); //线程A想要1资源，但是线程B已经将1资源加锁，错误代码
            command_message_.push_back(i);
            my_mutex1_.unlock();
            my_mutex2_.unlock();
        }
    }

    void OutGetMessage() {
        for (int i = 0; i < 10000;) {
            // 1.两个互斥量都加锁
            my_mutex1_.lock();
            my_mutex2_.lock();
            // 2. lock()方法
            /*
            // std::lock()方式加锁
            std::lock(my_mutex1_, my_mutex2_);
            // 使用lock()加锁，lock_guard防止没有调用unlock()函数
            std::lock_guard <std::mutex> guard_mutex1(my_mutex1_, std::adopt_lock);
            std::lock_guard <std::mutex> guard_mutex2(my_mutex2_, std::adopt_lock);
            */

            if (command_message_.empty()) {
                std::cout << "command_message is empty(), nothing to do" << std::endl;

            }
            else {
                i++;
                std::cout << "get command out list"
                          << command_message_.front()
                          << std::endl;
                command_message_.pop_front();
            }
            my_mutex1_.unlock();
            my_mutex2_.unlock();
        }
    }
private:
    std::list<int>  command_message_;
    std::mutex my_mutex1_;
    std::mutex my_mutex2_;
};


int main() {
    A a;
    std::thread thread1(&A::InRecvMessage, &a);
    std::thread thread2(&A::OutGetMessage, &a);
    thread1.join();
    thread2.join();


    return 0;
}

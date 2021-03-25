#include <iostream>
#include <thread>
#include <list>
#include <mutex>

class A {
public:
    void InRecvMessage() {
        for (int i = 0; i < 10000; i++) {
            std::cout << "put command in list" << i << std::endl;
            my_mutex_.lock();
            command_message_.push_back(i);
            my_mutex_.unlock();
        }
    }

    void OutGetMessage() {
        for (int i = 0; i < 10000;) {
            my_mutex_.lock();
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
            my_mutex_.unlock();
        }
    }
private:
    std::list<int>  command_message_;
    std::mutex my_mutex_;
};


int main() {
    A a;
    std::thread thread1(&A::InRecvMessage, &a);
    std::thread thread2(&A::OutGetMessage, &a);
    thread1.join();
    thread2.join();


    return 0;
}

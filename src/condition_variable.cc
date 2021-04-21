#include <iostream>
#include <thread>
#include <list>
#include <mutex>
#include <condition_variable>

class MessageController {
public:
    void GetMessage() {
        /*
         wait函数的用法，用来等一个东西
         如果wait有第二个参数，lambda表达式，返回结果，如果为false，进程阻塞在wait行，为true程序往下进行
         notify_one用于通知该线程，将该线程唤醒，被唤醒之后干什么呢
         a) wait()尝试不断的尝试获取锁，如果获取不到，将卡在wait线程，
         b) 如果获取到锁
            1. wait没有第二个参数，第一次调用默认条件不成立，直到解锁互斥量并阻塞到本行，无条件地执行后面的程序
            2. 第二个参数返回为false，wait解锁互斥量，又睡眠，等待再次被唤醒
            3. 有第二个参数且返回为true，执行wait下面的函数

         缺点：
         （1） wait线程获取锁的概率比notify_one的线程低，也就是说生成者比消费者走的快，可以尝试多开两个消费者
         （2） wait下面的函数如果提前解锁，此时系统可能切换到其他线程，会导致其他线程的notify_one，并找不到对应的wait线程

         notify_all
         当wait的线程比较多的的时候，将所有wait的线程都开启。
        */

        while (is_started_) {
            int command;
            std::unique_lock<std::mutex> unique_lock2(mutex1_);

            while (is_started_ && command_.empty()) {
                cond_variable_.wait(unique_lock2);
            }
            command = command_.front();
            command_.pop_front();
            std::cout << "get " << command << "\t"
                      << " thread_id:" << std::this_thread::get_id()
                      << std::endl;
            //mutex1_.unlock();
            // 提前解锁，处理其他命令，缺点:有可能会切换到其他线程的notify_one，找不到对应的wait
        }
        //lambda 表达式： [ capture-list ] ( params ) -> ret { body }
        // capture-list: 它使这个匿名函数可以访问外部（父作用域）变量，在类中就是添加this，
        //               捕捉方式有按值和按引用两种。比如[a, &b]表示按值捕捉a，
        //               按引用捕捉b；[&, a]表示按引用捕捉所有父作用域变量，除了a按值捕捉，
        //               [=，&b]表示按值捕捉所有父作用域变量，除了b按引用捕捉。
        // params： 表达式传递的参数
        // ret：返回结果

    }
    void PutMessage() {
        {
            std::unique_lock<std::mutex> lock1(mutex1_);
            is_started_ = true;
        }
        for (int i = 0; i < 1000; i++) {
            std::unique_lock<std::mutex> lock1(mutex1_);
            command_.push_back(i);
            std::cout << "put " << i << "\t"
                      << " thread_id:" << std::this_thread::get_id()
                      << std::endl;
            cond_variable_.notify_one();
        }
        {
            std::unique_lock<std::mutex> lock1(mutex1_);
            is_started_ = false;
            cond_variable_.notify_one();
        }
    }

    std::list<int> command_;
    std::mutex mutex1_;
    std::condition_variable cond_variable_;
    bool is_started_ = false;
};


int main() {
    MessageController command_control;
    std::thread t1(&MessageController::PutMessage, &command_control);
    std::thread t2(&MessageController::GetMessage, &command_control);
    t1.join();
    t2.join();


    return 0;
}
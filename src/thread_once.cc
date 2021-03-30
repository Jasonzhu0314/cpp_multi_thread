#include <iostream>
#include <thread>
#include <mutex>



std::mutex mutex1;

class GCCollect {
public:
    ~GCCollect();
};


//单例设计模式，类只能申请一个实例
class MyCAS {
    friend GCCollect;
    // 使用一个类的析构函数对内存进行释放
    // (1) 友元函数方式类的私有变量，(2) 类中嵌套类的方式也可以
private:
    static MyCAS *my_instance_;

public:
    static MyCAS* CreatInstance() {
        //为了提高程序的执行效率，当my_instance_对象已经创建会后，不需要再进行加锁操作，省去加锁过程。
        if (my_instance_ == NULL) {
            std::unique_lock<std::mutex> unique_mutex(mutex1);
            // 如果不进行加锁，下面的代码会根据线程数，重复的执行，造成系统错误
            if (my_instance_ == NULL) {
                std::cout << "MyCAS CreatInstance func " << std::endl;
                my_instance_ = new MyCAS();
                static GCCollect cl;
                // 静态变量对象，程序结束的时候会执行GC析构函数，gc释放my_instance_
            }
        }
        return my_instance_;
    }
    void func() {
        std::cout << "class func" << std::endl;
    }

private:
    MyCAS() {}; // 私有化构造函数
};

MyCAS* MyCAS::my_instance_ = NULL;

GCCollect::~GCCollect() {
    if (MyCAS::my_instance_ != NULL){
        delete MyCAS::my_instance_;
        MyCAS::my_instance_ = NULL;
        std::cout << "GC deconstruct func" << std::endl;
    }
}

void TestThread() {

    MyCAS* ptr = MyCAS::CreatInstance();
    std::cout << "Test single instance func" << std::endl;

}



int main() {

//    MyCAS* ptr = MyCAS::CreatInstance();
//    MyCAS* ptr1 = MyCAS::CreatInstance();
//    ptr->func();
//    std::cout << "ptr address: " << ptr << std::endl;
//    std::cout << "ptr1 address: " << ptr1 << std::endl;

    //MyCAS a; // 构造函数私有化，只能通过类的静态成员函数创建对象

    std::thread thread1(TestThread);
    std::thread thread2(TestThread);
    thread1.join();
    thread2.join();

    return 0;
}
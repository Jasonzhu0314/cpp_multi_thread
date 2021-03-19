# cpp_multi_thread

#### 介绍
c++多线程开发

#### 软件架构
软件架构说明

### 多线程基础知识
常用的函数join

#### 线程的创建
包含的头文件`#include <thread>`
thread是一个类
```c++
//myprint 可调用对象，可以是函数，也可以是类变成仿函数。
thread myobj(myprint) 
// （1）当前代码是创建了线程，线程执行的起点(入口) myprint,
// (2) myprint()开始执行
myobj.join() // 阻塞主线程，等待子线程执行完后，再执行
```

#### 线程的控制
1. join
阻塞主线程，等待子线程执行完后，主线程再接着执行 

2. detach
将子线程和主线程分离，分开执行两个线程，但是当主线程执行过快时，会出现子线程没有执行完的情况

3. joinable
调用`join()`的行为，还清理了线程相关的存储部分，这样`std::thread` 对象将不再与已经完成的线程有任何关联。这意味着，只能对一个线程使用一次join();一
旦已经使用过`join()`，`std::thread`对象就不能再次加入了，当对其使用`joinable()`时，将返回否（false）



#### 安装教程

1.  xxxx
2.  xxxx
3.  xxxx

#### 使用说明

1.  xxxx
2.  xxxx
3.  xxxx

#### 参与贡献

1.  Fork 本仓库
2.  新建 Feat_xxx 分支
3.  提交代码
4.  新建 Pull Request


#### 特技

1.  使用 Readme\_XXX.md 来支持不同的语言，例如 Readme\_en.md, Readme\_zh.md
2.  Gitee 官方博客 [blog.gitee.com](https://blog.gitee.com)
3.  你可以 [https://gitee.com/explore](https://gitee.com/explore) 这个地址来了解 Gitee 上的优秀开源项目
4.  [GVP](https://gitee.com/gvp) 全称是 Gitee 最有价值开源项目，是综合评定出的优秀开源项目
5.  Gitee 官方提供的使用手册 [https://gitee.com/help](https://gitee.com/help)
6.  Gitee 封面人物是一档用来展示 Gitee 会员风采的栏目 [https://gitee.com/gitee-stars/](https://gitee.com/gitee-stars/)

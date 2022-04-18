/**
 * @file Singleton.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-18
 * 
 * @copyright Copyright (c) 2022
 * 
 * 单例模式可以分为懒汉式和饿汉式，两者之间的区别在于创建实例的时间不同：
 * 懒汉式：指系统运行中，实例并不存在，只有当需要使用该实例时，才会去创建并使用实例。（这种方式要考虑线程安全）
 * 饿汉式：指系统一运行，就初始化创建实例，当需要时，直接调用即可。（本身就线程安全，没有多线程的问题）
 * 
 * 特点：
 * 1 构造函数和析构函数为private类型，目的禁止外部构造和析构。
 * 2 拷贝构造和赋值构造函数为private类型，目的是禁止外部拷贝和赋值，确保实例的唯一性。
 * 3 类里有个获取实例的静态函数，可以全局访问。
 * 
 */

#ifndef _SINGLETON_H_
#define _SINGLETON_H_


#include <iostream>

template <typename T>
class Singleton {
public:
    static T &GetInstance();

private:
    Singleton() = default;
    Singleton(const Singleton &) = delete;
    Singleton &operator=(const Singleton &) = delete;
    ~Singleton() = default;
};

/* 线程不安全 */
// template <typename T>
// T* Singleton<T>::Instance() {
//     if (instance_ == nullptr) {
//         instance_ = new T();
//     }
//     return instance_;
// }


/**
 * @brief 
 * 
 * 使用了C++11的特性，在C++11内部静态变量的方式里是线程安全的
 * 
 * @tparam T 
 * @return T& 
 */
template <typename T>
T &Singleton<T>::GetInstance() {
    
    static T instance;
    return instance;
}

int main () {
    
    auto& t1 = Singleton<int>::GetInstance();
    auto& t2 = Singleton<int>::GetInstance();
    std::cout << "t1 point to: "  << &t1 << std::endl;
    std::cout << "t2 point to: "  << &t2 << std::endl;

    return 0;
}


#endif
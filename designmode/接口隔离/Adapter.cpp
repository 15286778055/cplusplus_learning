/**
 * @file Adapter.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-19
 * 
 * @copyright Copyright (c) 2022
 * 
 * 适配器模式：c++ STL 中 stack、queue 就是适配器，原型是 deque
 * 对象适配器：继承接口、组合原型
 * 类适配器：多继承
 * 
 * 
 * 适配器和代理模式的区别
 * 实现上面：
 * 1 适配器 继承 目标接口（需要重写这个接口），组合 被适配者（使用被适配者的接口实现继承来的目标接口）
 * 2 代理 继承 被代理对象（需要重写这个接口），组合 被代理对象（添加特殊操作、封装被代理对象的接口）
 * 
 * 适配器 有两个对象，一个“目标接口”，一个“被适配对象”
 * 代理 仅针对一个对象，"代理对象"，无目标接口
 * 
 */

#include <iostream>
#include <memory>

class Target {
public:
    virtual void Print() = 0;
    virtual ~Target() = default;
};

class Adaptee {
public:
    virtual void PrintImpl() { std::cout << "Print Impl" << std::endl; }
    virtual ~Adaptee() = default;
};

/* 类适配器 */
// class Adatper : public Target, public Adaptee {
// public:
//     virtual void Print() override { Adaptee::PrintImlp(); }
// };

/* 对象适配器 */
class Adapter : public Target {     /* 继承需要实现的接口 */
public:
    Adapter() : adaptee_(new Adaptee()) {}
    
    Adaptee &GetAdaptee() {
        if (!adaptee_) {
            adaptee_ = new Adaptee();
        }
        return *adaptee_;
    }

    virtual void Print() override {
        // to fix the interface of adaptee to meet the interface inherited
        std::cout << "begin of adaptee" << std::endl;
        std::cout << "to fix the interface of adaptee to meet the interface inherited" << std::endl;

        GetAdaptee().PrintImpl();

        std::cout << "end of adaptee" << std::endl;
    }
    
    virtual ~Adapter() {
        delete adaptee_;
    }


/* 组合被适配者，用于实现继承的接口 */
private:
    Adaptee *adaptee_;
};


int main() {

    Adapter a = Adapter();
    a.Print();

    return 0;
}

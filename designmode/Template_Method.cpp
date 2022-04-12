/**
 * @file Template_Method.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-12
 * 
 * @copyright Copyright (c) 2022
 * 
 * 1 晚绑定 运行时多态
 * 2 父类 / 类库 规定好流程，规定好函数函数接口（规定好 模版方法）， 子类实现接口， 利用虚指针 动态绑定子类的实现
 * 
 */


#include <iostream>
// #include <memory>

class Abstract {

public:
    void TemplateMethod() {
        FunctionA();
        FunctionB();
        FunctionC();
    }

    virtual ~Abstract() = default;

private:
    virtual void FunctionA() = 0;       /* = 0 means pure virtual function */
    virtual void FunctionB() = 0;
    virtual void FunctionC() = 0;
};


class A : public Abstract {

private:
    void FunctionA() override { std::cout << 1 << std::endl; }
    void FunctionB() override { std::cout << 2 << std::endl; }
    void FunctionC() override { std::cout << 3 << std::endl; }
};

class B : public Abstract {

private:
    void FunctionA() override { std::cout << 4 << std::endl; };
    void FunctionB() override { std::cout << 5 << std::endl; };
    void FunctionC() override { std::cout << 6 << std::endl; };
};

int main() {

    /* support by c++14 */
    std::unique_ptr<Abstract> a = std::make_unique<A>();
    std::unique_ptr<Abstract> b = std::make_unique<B>();
    
    /* support by c++11 */
    // Abstract *a = new A();
    // Abstract *b = new B();

    a->TemplateMethod();
    b->TemplateMethod();

    return 0;
}
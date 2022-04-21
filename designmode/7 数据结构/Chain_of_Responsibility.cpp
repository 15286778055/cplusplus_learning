/**
 * @file Chain_of_Responsibility.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-21
 * 
 * @copyright Copyright (c) 2022
 * 
 * 责任链：链表
 * 
 */

#include <cstdint>
#include <iostream>
#include <memory>
#include <utility>

class Handler {
public:
    virtual void Process(std::int32_t i) {
        if (p_) {
            p_->Process(i);
        } else {
            std::cout << i << "can't be processed\n";
        }
    }

    void SetNext(std::shared_ptr<Handler> p) { p_ = p; }

    virtual ~Handler() = default;

private:
    std::shared_ptr<Handler> p_;
};

class A : public Handler {
public:
    virtual void Process(std::int32_t i) override {
        if (i < 10) {
            std::cout << i << " processed by A" << std::endl;
        } else {
            Handler::Process(i);
        }
    }
};

class B : public Handler {
public:
    virtual void Process(std::int32_t i) override {
        if (i < 100) {
            std::cout << i << " processed by B" << std::endl;
        } else {
            Handler::Process(i);
        }
    }
};

class C : public Handler {
public:
    virtual void Process(std::int32_t i) override {
        if (i < 1000) {
            std::cout << i << " processed by C" << std::endl;
        } else {

            /**
             * @brief Construct a new Handler:: Process object
             * 调用基类同名函数，用基类指针的函数来接着处理
             * 如果按照常规方法（分别直接实现 Handler::Process() ），这三段代码是完全重复的，
             * 通过 “重构” ，也可以写出目前这种结构
             * 
             * 也不一定马上就能写出这种代码，最重要的还是要 不断 “重构”
             * 
             */

            Handler::Process(i);
        }
    }
};


int main() {
    auto a = std::make_shared<A>();
    auto b = std::make_shared<B>();
    auto c = std::make_shared<C>();

    /* 责任链 链接 */
    a->SetNext(b);
    b->SetNext(c);

    a->Process(999);

}
/**
 * @file Strategy.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-12
 * 
 * @copyright Copyright (c) 2022
 * 
 * 1 使用场景：某一个环境/上下文中 ， if else （bad smell） 替换为 strategy 模式
 * 
 */


#include <iostream>
// #include <memory>

class Strategy {

public:
    virtual void Print() = 0;
    virtual ~Strategy() = default;
};


class StrategyA : public Strategy {

public:
    void Print() override { std::cout << "StrategyA" << std::endl; }
};

class StrategyB : public Strategy {
    void Print() override { std::cout << "StrategyB" << std::endl; }
};

/* 使用上下文(场景) */
class Context {
public:
    Context(std::unique_ptr<Strategy> p) : p_(std::move(p)) {}

    void Print() const { p_->Print(); }

private:
    std::unique_ptr<Strategy> p_;
};


int main() {

    Context a{std::make_unique<StrategyA>()};
    Context b{std::make_unique<StrategyB>()};

    a.Print();
    b.Print();

    return 0;
}
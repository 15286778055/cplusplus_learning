/**
 * @file State2.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-21
 * 
 * @copyright Copyright (c) 2022
 * 
 * 状态模式：指针实现
 * 
 */

#include <iostream>
#include <memory>

/* state */
class State {
public:
    virtual void Operation1() = 0;
    virtual void Operation2() = 0;
    virtual ~State() = default;
};

class StateA : public State {
public:
    virtual void Operation1() override {
        std::cout << "operation1 in stateA" << std::endl;
    }

    virtual void Operation2() override {
        std::cout << "operation2 in stateA" << std::endl;
    }
};

class StateB : public State {
public:
    virtual void Operation1() override {
        std::cout << "operation1 in stateB" << std::endl;
    }

    virtual void Operation2() override {
        std::cout << "operation2 in stateB" << std::endl;
    }
};

/* Processor */
class Processor {
public:
    explicit Processor(State *current_state) : current_state_(current_state) {}
    
    /* 更换状态 */
    void ChangeState(State *state) {
        current_state_ = state;
    }

    void Operation1() {
        current_state_->Operation1();
    }

    void Operation2() {
        current_state_->Operation2();
    }

    ~Processor() { if (current_state_) delete current_state_; }

private:
    State *current_state_;
};


int main() {
    Processor processor{new StateA()};
    processor.Operation1();
    processor.Operation2();
    processor.ChangeState(new StateB());
    processor.Operation1();
    processor.Operation2();
}
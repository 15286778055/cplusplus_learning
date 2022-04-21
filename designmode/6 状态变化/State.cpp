/**
 * @file State.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-21
 * 
 * @copyright Copyright (c) 2022
 * 
 * 状态模式：unique_ptr实现
 * 
 * 和 strategy 在于，一个保存的状态，一个直接重新创建对象。其实思想都一样
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

/**/
class Processor {
public:
    explicit Processor(std::unique_ptr<State> current_state) : current_state_(std::move(current_state)) {}
    
    /* 更换状态 */
    void ChangeState(std::unique_ptr<State> state) {
        current_state_ = std::move(state);
    }

    void Operation1() {
        current_state_->Operation1();    
    }

    void Operation2() {
        current_state_->Operation2();
    }

private:
    std::unique_ptr<State> current_state_;
};


int main() {
    Processor processor{std::make_unique<StateA>()};
    processor.Operation1();
    processor.Operation2();
    processor.ChangeState(std::make_unique<StateB>());
    processor.Operation1();
    processor.Operation2();
}
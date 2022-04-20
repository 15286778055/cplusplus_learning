/**
 * @file Mediator.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-20
 * 
 * @copyright Copyright (c) 2022
 * 
 * 实现：
 * 1 中介者模式 实现方式 与 观察者模式 实现方式 很像
 * 2 中介者有一个list，存有各个成员
 * 3 各个成员有一个 中介者指针，用于调用 通知应该通知的另外成员
 * 
 * 对比：
 * 1 中介者模式 由其中某个成员发起，调用成员中 中介者指针 的 Notify函数，进行广播或者消息传递
 * 2 观察者模式 由观察者发起消息通知
 * 3 不同在于 通知 的方式：广播（观察者一般采用）、针对性（中介者采用、如何针对性通知）
 * 
 */

#include <iostream>
#include <memory>
#include <list>
#include <string_view>
#include <utility>

class Colleague;

/* 中介者 Mediator */
class Mediator {
public:
    virtual void Notify(const std::shared_ptr<Colleague> &, std::string_view) = 0;
    virtual ~Mediator() = default;
};

/* 成员接口 */
class Colleague {
public:
    explicit Colleague(const std::shared_ptr<Mediator> &p) : mediator_(p) {}
    virtual void Send(std::string_view) = 0;
    virtual void Receive(std::string_view) const = 0;
    virtual ~Colleague() = default;

protected:
    std::weak_ptr<Mediator> mediator_;
};

class ColleagueA : public Colleague, public std::enable_shared_from_this<ColleagueA> {
public:
    explicit ColleagueA(const std::shared_ptr<Mediator> &p) : Colleague(p) {}

    virtual void Send(std::string_view s) override {
        mediator_.lock()->Notify(shared_from_this(), s);
    }

    virtual void Receive(std::string_view s) const override {
        std::cout << "A receive: " << s << std::endl;
    }
};

class ColleagueB : public Colleague, public std::enable_shared_from_this<ColleagueB> {
public:
    explicit ColleagueB(const std::shared_ptr<Mediator> &p) : Colleague(p) {}

    virtual void Send(std::string_view s) override {
        mediator_.lock()->Notify(shared_from_this(), s);
    }

    virtual void Receive(std::string_view s) const override {
        std::cout << "B receive: " << s << std::endl;
    }
};


/* 中介者 实现 */
class ConcreteMediator : public Mediator {
public:
    void Append(const std::shared_ptr<Colleague> &c) {
        colleagues_.emplace_back(c);
    }

    virtual void Notify(const std::shared_ptr<Colleague> &c, std::string_view s) override {
        for (auto &&x : colleagues_) {
            if (const auto p =  x.lock()) {
                if (p != c) {
                    p->Receive(s);      // transfer to other members
                }
            }
        }
    }

private:
    std::list<std::weak_ptr<Colleague>> colleagues_;
};


int main() {
    auto mediator = std::make_shared<ConcreteMediator>();
    auto colleagueA = std::make_shared<ColleagueA>(mediator);
    auto colleagueB = std::make_shared<ColleagueB>(mediator);

    mediator->Append(colleagueA);
    mediator->Append(colleagueB);

    colleagueA->Send("aa");
    colleagueB->Send("bb");
}
/**
 * @file Mediator.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-20
 * 
 * @copyright Copyright (c) 2022
 * 
 * 实现 2
 * 
 */

#include <iostream>
#include <memory>
#include <string_view>
#include <utility>
#include <unordered_map>
#include <string>
#include <list>

class Colleague;

/* 中介者 Mediator */
class Mediator {
public:
    /* version 1: 仅支持向 一个对象 传递 */
    // virtual void Notify(std::string from, std::string dir, std::string_view) = 0;
    /* version 2: 支持向多对象传递 */
    virtual void Notify(std::string from, std::list<std::string> dir, std::string_view) = 0;
    virtual ~Mediator() = default;

protected:
    std::unordered_map<std::string, std::weak_ptr<Colleague>> colleagues_;
};

/* 成员接口 */
class Colleague {
public:
    explicit Colleague(std::string name, const std::shared_ptr<Mediator> &p) : name_(name), mediator_(p) {}
    /* version 1: 仅支持向 一个对象 传递 */
    // virtual void Send(std::string dir, std::string_view content) {
    //     mediator_.lock()->Notify(name_, dir, content);
    // }
    /* version 2: 支持向多对象传递 */
    virtual void Send(std::list<std::string> dir, std::string_view content) {
        mediator_.lock()->Notify(name_, dir, content);
    }
    std::string Name() const { return name_; }
    virtual void Receive(std::string from, std::string_view content) const {
        std::cout << Name() << " receive: " << content << " from " << from << std::endl;
    }
    virtual ~Colleague() = default;

protected:
    std::weak_ptr<Mediator> mediator_;
    std::string name_;
};

class ColleagueA : public Colleague {
public:
    explicit ColleagueA(const std::shared_ptr<Mediator> &p) : Colleague("ColleagueA", p) {}

};

class ColleagueB : public Colleague, public std::enable_shared_from_this<ColleagueB> {
public:
    explicit ColleagueB(const std::shared_ptr<Mediator> &p) : Colleague("ColleagueB", p) {}

};

class ColleagueC : public Colleague, public std::enable_shared_from_this<ColleagueC> {
public:
    explicit ColleagueC(const std::shared_ptr<Mediator> &p) : Colleague("ColleagueC", p) {}

};

/* 中介者 实现 */
class ConcreteMediator : public Mediator {
public:
    void Append(std::string key, const std::shared_ptr<Colleague> &c) {
        colleagues_.emplace(key, c);
    }

    /* version 1: 仅支持向 一个对象 传递 */
    // virtual void Notify(std::string from, std::string dir, std::string_view content) override {
        
    //     if (auto i = colleagues_.find(dir); i != colleagues_.end()) {       /* c++17 特性 */
    //         if (const auto p = i->second.lock()) {
    //             p->Receive(from, content);
    //         }
    //     }
    // }

    /* version 2: 支持向多个对象传递 */
    virtual void Notify(std::string from, std::list<std::string> dir, std::string_view content) override {
        for (const auto &item : dir) {
            if (auto i = colleagues_.find(item); i != colleagues_.end()) {       /* c++17 特性 */
                if (const auto p = i->second.lock()) {
                    p->Receive(from, content);
                }
            }
        }
    }
};


int main() {
    auto mediator = std::make_shared<ConcreteMediator>();
    auto colleagueA = std::make_shared<ColleagueA>(mediator);
    auto colleagueB = std::make_shared<ColleagueB>(mediator);
    auto colleagueC = std::make_shared<ColleagueC>(mediator);

    mediator->Append(colleagueA->Name(), colleagueA);
    mediator->Append(colleagueB->Name(), colleagueB);
    mediator->Append(colleagueC->Name(), colleagueC);

    std::list<std::string> dir1 = { colleagueB->Name(), colleagueC->Name() };
    std::list<std::string> dir2 = { colleagueC->Name() };

    colleagueA->Send(dir1, "aa");
    colleagueB->Send(dir2, "bb");
}
#include <iostream>
#include <memory>
#include <list>


class Subject;

/* Observer */
class Observer {
public:
    explicit Observer(const std::shared_ptr<Subject>& p) : subject_(p) {}
    virtual void Update() = 0;
    virtual ~Observer() = default;

protected:
    /**
     * @brief 一种是给 update 函数一个参数，这样就可以通过参数 获取订阅了什么值，
     * 这里给的是地址。
     * 两种各有利弊：
     * 安全性：一个是 固定参数（固定类型），一个是地址，完全获取了被订阅者的地址，那么可以访问其中的所有public方法，安全性？？
     * 扩展性：前者接口太固定，修改参数需要修改接口；后者利于扩展
     * 
     */
    std::weak_ptr<Subject> subject_;        /* the pointer is used to record the broadcast address, call the function, get the needed value */
};

/* Pub */
class Subject {
public:
    void Append(const std::shared_ptr<Observer>& o) {
        observers_.emplace_back(o);
    }

    void Remove(const std::shared_ptr<Observer>& o) { observers_.remove(o); }

    void Notify() {
        for (auto& x : observers_) x->Update();
    }

    void SetValue(std::int32_t n) { value_ = n; }

    std::int32_t Value() { return value_; }

private:
    std::list<std::shared_ptr<Observer>> observers_;        /* list could be add/remove easily */
    std::int32_t value_ = 0;        /* value to notify */
};

/* Observer A */
class ObserverA : public Observer {
public:

    /* 以下两行为 class ObserverA 提供构造函数，默认构造函数是无参的，但 main里面会传递 subject 来构造，找不到复合条件的函数 */
    using Observer::Observer;        /* 编译器会提供默认构造函数，但无法满足 main 里面的构造，这句代码引入父类的构造函数，满足调用条件 */
    // ObserverA(const std::shared_ptr<Subject>& p) : Observer(p) {}        /* 直接提供一个函数 */

    void Update() override {
        if (const auto p = subject_.lock()) {
            std::cout << "Subject value in A: " << p->Value() << std::endl;
        }
    }
};

/* Observer B */
class ObserverB : public Observer {
public:
    using Observer::Observer;

    void Update() override {
        if (const auto p = subject_.lock()) {
            std::cout << "Subject value in B: " << p->Value() << std::endl;
        }
    }
};





int main() {
    auto subject = std::make_shared<Subject>();
    auto a = std::make_shared<ObserverA>(subject);
    auto b = std::make_shared<ObserverB>(subject);

    subject->Append(a);
    subject->Append(b);
    
    subject->SetValue(5);
    subject->Notify();

    return 0;
}
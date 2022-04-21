/**
 * @file Composite.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-21
 * 
 * @copyright Copyright (c) 2022
 * 
 * 组合模式：树形结构
 * 
 * 
 */

#include <iostream>
#include <list>
#include <memory>
#include <algorithm>

class ComponentBase {
public:
    virtual void Append(const std::shared_ptr<ComponentBase> &) {}
    virtual void Remove(const std::shared_ptr<ComponentBase> &) {}
    virtual void Process() = 0;
    virtual ~ComponentBase() = default;
};

class Component1 : public ComponentBase {
public:
    virtual void Process() {
        std::cout << "Component1: process" << std::endl;
    }
};

class Component2 : public ComponentBase {
public:
    virtual void Process() {
        std::cout << "Component2: process" << std::endl;
    }
};

class Composite : public ComponentBase {
public:
    virtual void Append(const std::shared_ptr<ComponentBase> &c) override {
        composite_.emplace_back(c);
    }

    virtual void Remove(const std::shared_ptr<ComponentBase> &c) override {
        if (const auto it = std::find(composite_.cbegin(), composite_.cend(), c); it != std::cend(composite_)) {
            composite_.erase(it);
        }
    }
    
    virtual void Process() override {
        for (auto &&it : composite_ ) {
            it->Process();
        }
    }

private:
    std::list<std::shared_ptr<ComponentBase>> composite_;
};

int main() {
    std::unique_ptr<ComponentBase> pc = std::make_unique<Composite>();
    
    std::shared_ptr<ComponentBase> pc2 = std::make_shared<Composite>();

    const auto c1 = std::make_shared<Component1>();
    const auto c2 = std::make_shared<Component1>();
    const auto c3 = std::make_shared<Component2>();
    const auto c4 = std::make_shared<Component2>();

    pc->Append(c1);
    pc->Append(c2);
    pc->Append(pc2);
    pc2->Append(c3);
    pc2->Append(c4);

    
    
    pc->Process();


    return 0;
}
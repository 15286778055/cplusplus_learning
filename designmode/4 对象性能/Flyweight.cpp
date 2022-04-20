/**
 * @file Flyweight.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-19
 * 
 * @copyright Copyright (c) 2022
 * 
 * 享元模式：键值对记录对象，避免多次创建，对内存资源的过多消耗
 * 
 */

#include <iostream>
#include <unordered_map>
#include <memory>

class Flyweight {
public:
    virtual void Print() = 0;
    virtual ~Flyweight() = default;
};

class ConcreteFlyweight : public Flyweight {
public:
    explicit ConcreteFlyweight(char key) : key_(key) {}
    virtual void Print() override { std::cout << key_ << std::endl; }

private:
    char key_;
};

class FlyweightFactory {
public:
    std::unique_ptr<Flyweight> &FlyweightPtr(char c) {
        if (const auto it = m_.find(c); it != std::end(m_)) {
            std::cout << "existing key: ";
            return it->second;
        }
        std::unique_ptr<Flyweight> p = std::make_unique<ConcreteFlyweight>(c);
        m_.emplace(c, std::move(p));
        return m_.at(c);
    }

private:
    std::unordered_map<char, std::unique_ptr<Flyweight>> m_;
};


int main() {
    FlyweightFactory factory;
    factory.FlyweightPtr('a')->Print();
    factory.FlyweightPtr('a')->Print();
    factory.FlyweightPtr('b')->Print();
    factory.FlyweightPtr('b')->Print();
}
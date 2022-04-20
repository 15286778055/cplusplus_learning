/**
 * @file Prototype.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-15
 * 
 * @copyright Copyright (c) 2022
 * 
 * 针对复杂对象创建
 * 
 */

#include <iostream>
#include <memory>

class Prototype {
public:
    virtual std::unique_ptr<Prototype> Clone() = 0;
    virtual ~Prototype() = default;
};

class A : public Prototype {
public:
    virtual std::unique_ptr<Prototype> Clone() override {
        return std::make_unique<A>(*this);
    }
};

int main() {
    std::unique_ptr<Prototype> p = std::make_unique<A>();
    std::cout << "I am a A, my address is: " << &(*p) << std::endl;
    std::cout << "I am a A, the address of the unique_pointer point to me is: " << &p << std::endl;
    std::unique_ptr<Prototype> q;
    for (int i = 0; i < 5; ++i) {
        q = p->Clone();
        std::cout << i << std::endl;
        std::cout << "\tI am also a A, my address is: " << &(*q) << std::endl;
        std::cout << "\tI am also a A, the address of the unique_pointer point to me is: " << &q << std::endl;
    }
    

    return 0;
}
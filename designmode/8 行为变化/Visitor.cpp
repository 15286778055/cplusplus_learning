/**
 * @file Visitor.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-22
 * 
 * @copyright Copyright (c) 2022
 * 
 * 访问者模式
 * 通过双重分发（两次多态辨析），在不更改Element类层次结构的前提下，为各个类添加新操作
 * 
 * 使用条件：Element的派生类确定、无变化（稳定），派生类需要添加功能（变化）
 * 
 */

#include <iostream>
#include <memory>


/***** 稳定部分 *****/

/* Visitor */
class Visitor;

/* Element */
class Element {
public:
    virtual void Accept(Visitor &visitor) = 0;      /* 这个已经把调用此visitor的element记下来了，可以访问其公有成员 */
    virtual ~Element() = default;
};

class Visitor {
public:
    virtual void VisitA(const Element &) = 0;
    virtual void VisitB(const Element &) = 0;
    virtual ~Visitor() = default;
};

class ElementA : public Element {
    virtual void Accept(Visitor &visitor) override {
        visitor.VisitA(*this);
    }

};

class ElementB : public Element {
    virtual void Accept(Visitor &visitor) override {
        visitor.VisitB(*this);
    }
};



/***** 变化部分 *****/

class ConcreteVisitor : public Visitor {
public:
    virtual void VisitA(const Element &ele) override {
        std::cout << "concrete visitor for element A" << std::endl;
    }

    virtual void VisitB(const Element &ele) override {
        std::cout << "concrete visitor for element B" << std::endl;
    }
};

int main() {
    Element *a = new ElementA();
    Element *b = new ElementB();
    Visitor *v = new ConcreteVisitor();

    a->Accept(*v);
    b->Accept(*v);

    delete a;
    delete b;
    delete v;

}
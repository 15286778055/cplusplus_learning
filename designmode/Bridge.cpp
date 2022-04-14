#include <iostream>
#include <memory>

/* Abstraction implementation */
class AbstractionImpl {
public:
    virtual void PrintImpl() = 0;
    virtual ~AbstractionImpl() = default;
};

class AImpl1 : public AbstractionImpl {
public:
    virtual void PrintImpl() override { std::cout << "AImpl1" << std::endl; }
};

class AImpl2 : public AbstractionImpl {
public:
    virtual void PrintImpl() override { std::cout << "AImpl2" << std::endl; }
};


/* Abstraction */
class Abstraction {
public:
    virtual void Print() = 0;
    virtual ~Abstraction() = default;
};

class A1 : public Abstraction {
public:
    explicit A1(std::unique_ptr<AbstractionImpl> p) : p_(std::move(p)) {}

    virtual void Print() override {
        std::cout << "in Abstraction1, call AImlp1" << std::endl;
        p_->PrintImpl();
    }

private:
    std::unique_ptr<AbstractionImpl> p_;
};

class A2 : public Abstraction {
public:
    explicit A2(std::unique_ptr<AbstractionImpl> p) : p_(std::move(p)) {}

    virtual void Print() override {
        std::cout << "in Abstraction1, call AImlp1" << std::endl;
        p_->PrintImpl();
    }

private:
    std::unique_ptr<AbstractionImpl> p_;
};



int main() {

    std::unique_ptr<Abstraction> a1 = std::make_unique<A1>(std::make_unique<AImpl1>());
    std::unique_ptr<Abstraction> a2 = std::make_unique<A1>(std::make_unique<AImpl2>());
    std::unique_ptr<Abstraction> a3 = std::make_unique<A2>(std::make_unique<AImpl1>());
    std::unique_ptr<Abstraction> a4 = std::make_unique<A2>(std::make_unique<AImpl2>());

    a1->Print();
    a2->Print();
    a3->Print();
    a4->Print();

    return 0;
}
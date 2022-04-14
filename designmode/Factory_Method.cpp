#include <iostream>
#include <memory>
#include <string>

/* Base class */
class Base {
public:
    explicit Base(std::string name) : name_(name) {}
    virtual ~Base() = default;
    std::string Name() const { return name_; }

protected:
    std::string name_;
};

class Child1 : public Base {
public:
    explicit Child1(std::string name) : Base(name) {}
};

class Child2 : public Base {
public:
    explicit Child2(std::string name) : Base(name) {}
};


/* Factory */
class BaseFactory {
public:
    virtual Base *CreateBase() = 0;
    virtual ~BaseFactory() = default;
};

class Child1Factory : public BaseFactory {
public:
    virtual Base *CreateBase() override {
        return new Child1("Child1");
    }
};

class Child2Factory : public BaseFactory {
public:
    virtual Base *CreateBase() override {
        return new Child2("Child2");
    }
};


/* Some test class need to use factory method to dynamically generate class */
class SomeTestClass {
public:
    explicit SomeTestClass(BaseFactory *factory) : factory_(factory) {}
    Base *CreateBase() { return factory_->CreateBase(); }
    ~SomeTestClass() { delete factory_; }

private:
    BaseFactory *factory_;
};



int main() {

    
    SomeTestClass test(new Child2Factory());
    Base *pb = test.CreateBase();
    std::cout << pb->Name() << std::endl;
    delete pb;

    
    
    // BaseFactory *pf = nullptr;
    
    // pf = new Child2Factory();
    // pb = CreateBase(pf);
    // std::cout << pb->Name() << std::endl;
    // delete pb;
    // delete pf;

    // pf = new Child1Factory();
    // pb = CreateBase(pf);
    // std::cout << pb->Name() << std::endl;
    // delete pb;
    // delete pf;

    return 0;
}
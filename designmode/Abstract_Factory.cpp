#include <iostream>
#include <memory>
#include <string>

/* Base class */
class Base1 {
public:
    explicit Base1(std::string name) : name_(name) {}
    virtual ~Base1() = default;
    std::string Name() const { return name_; }

protected:
    std::string name_;
};

class Base2 {
public:
    explicit Base2(std::string name) : name_(name) {}
    virtual ~Base2() = default;
    std::string Name() const { return name_; }

protected:
    std::string name_;
};

class Base3 {
public:
    explicit Base3(std::string name) : name_(name) {}
    virtual ~Base3() = default;
    std::string Name() const { return name_; }

protected:
    std::string name_;
};


/* 特定系列1 */
class XBase1 : public Base1 {
public:
    explicit XBase1(std::string name) : Base1(name) {}
};

class XBase2 : public Base2 {
public:
    explicit XBase2(std::string name) : Base2(name) {}
};

class XBase3 : public Base3 {
public:
    explicit XBase3(std::string name) : Base3(name) {}
};

/* 特定系列2 */
class YBase1 : public Base1 {
public:
    explicit YBase1(std::string name) : Base1(name) {}
};

class YBase2 : public Base2 {
public:
    explicit YBase2(std::string name) : Base2(name) {}
};

class YBase3 : public Base3 {
public:
    explicit YBase3(std::string name) : Base3(name) {}
};


/* Abstract Factory */
class BaseFactory {
public:
    virtual Base1 *CreateBase1() = 0;
    virtual Base2 *CreateBase2() = 0;
    virtual Base3 *CreateBase3() = 0;
    virtual ~BaseFactory() = default;
};

/* 系列工厂 */
class XFactory : public BaseFactory {
public:
    virtual Base1 *CreateBase1() override {
        return new XBase1("XChild1");
    }
    virtual Base2 *CreateBase2() override {
        return new XBase2("XChild2");
    }
    virtual Base3 *CreateBase3() override {
        return new XBase3("XChild3");
    }
};

class YFactory : public BaseFactory {
public:
    virtual Base1 *CreateBase1() override {
        return new YBase1("YChild1");
    }
    virtual Base2 *CreateBase2() override {
        return new YBase2("YChild2");
    }
    virtual Base3 *CreateBase3() override {
        return new YBase3("YChild3");
    }
};


/* Some test class need to use factory method to dynamically generate class */
class SomeTestClass {
public:
    explicit SomeTestClass(BaseFactory *factory) : factory_(factory) {}
    Base1 *CreateBase1() { return factory_->CreateBase1(); }
    Base2 *CreateBase2() { return factory_->CreateBase2(); }
    Base3 *CreateBase3() { return factory_->CreateBase3(); }
    ~SomeTestClass() { delete factory_; }

private:
    BaseFactory *factory_;
};



int main() {

    
    SomeTestClass test(new YFactory());
    Base1 *pb1 = test.CreateBase1();
    Base2 *pb2 = test.CreateBase2();
    Base3 *pb3 = test.CreateBase3();
    std::cout << pb1->Name() << std::endl;
    std::cout << pb2->Name() << std::endl;
    std::cout << pb3->Name() << std::endl;
    delete pb1;
    delete pb2;
    delete pb3;

    
    

    return 0;
}
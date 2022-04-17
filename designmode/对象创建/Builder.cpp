#include <iostream>
#include <string>

/* Base */
class Base {
public:
    virtual void CreateComp1() {}
    virtual void CreateComp2() {}
    virtual void CreateComp3() {}
    std::string Name() const { return name_; }
    virtual ~Base() = default;

protected:
    std::string name_;
};

class Child1 : public Base {
public:
    explicit Child1() { name_ = "Child1"; }
    virtual void CreateComp1() override {

    }

    virtual void CreateComp2() override {

    }

    virtual void CreateComp3() override {

    }
};

/* Builder */
class Builder {
public:
    explicit Builder(Base *base) : base_(base) {}
    virtual void BuildComp1() = 0;
    virtual void BuildComp2() = 0;
    virtual void BuildComp3() = 0;
    virtual Base *GetBuild() const { return base_; }
    virtual ~Builder() = default;
    
protected:
    Base *base_;
};

class Child1Builder : public Builder {
public:
    explicit Child1Builder() : Builder(new Child1()) {}
    virtual void BuildComp1() override {
        base_->CreateComp1();
        std::cout << "\tChild1Builder comp1" << std::endl;
    }
    virtual void BuildComp2() override {
        base_->CreateComp2();
        std::cout << "\tChild1Builder comp2" << std::endl;
    }
    virtual void BuildComp3() override {
        base_->CreateComp3();
        std::cout << "\tChild1Builder comp2" << std::endl;
    }
};

// class AdvanceBuilder2 : public Builder {
// public:
//     virtual void BuildComp1() override {
//         base_->CreateComp1();
//         std::cout << "\tAdvanceBuilder2 comp1" << std::endl;
//     }
//     virtual void BuildComp2() override {
//         base_->CreateComp2();
//         std::cout << "\tAdvanceBuilder2 comp2" << std::endl;
//     }
//     virtual void BuildComp3() override {
//         base_->CreateComp3();
//         std::cout << "\tAdvanceBuilder2 comp3" << std::endl;
//     }
// };

/* test */
class Test {
public:
    Test(Builder *builder) : builder_(builder) {}

    /* 这个构建 base 的流程固定，这部分是稳定的 */
    Base *TestFuc() {
        builder_->BuildComp1();
        builder_->BuildComp2();
        builder_->BuildComp3();
        return builder_->GetBuild();
    }

private:
    Builder *builder_;
};

int main() {


    Test t(new Child1Builder());
    Base *pb = t.TestFuc();
    std::cout << pb->Name() << std::endl;

    return 0;
}
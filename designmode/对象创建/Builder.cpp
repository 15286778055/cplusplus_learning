#include <iostream>

/* Base */
class Base {
public:
    virtual void CreateComp1() {}
    virtual void CreateComp2() {}
    virtual void CreateComp3() {}
    virtual ~Base() = default;
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
    
private:
    Base *base_;
};

class AdvanceBuilder1 : public Builder {
public:
    explicit AdvanceBuilder1(Base *base) : Builder(base) {}
    virtual void BuildComp1() override {

        base_->CreateComp1();




        std::cout << "\tAdvanceBuilder1 comp1" << std::endl;
    }
    virtual void BuildComp2() override {
        std::cout << "\tAdvanceBuilder1 comp2" << std::endl;
    }
    virtual void BuildComp3() override {
        std::cout << "\tAdvanceBuilder1 comp2" << std::endl;
    }
};

class AdvanceBuilder2 : public Builder {
public:
    explicit AdvanceBuilder2(Base *base) : Builder(base) {}
    virtual void BuildComp1() override {
        std::cout << "\tAdvanceBuilder2 comp1" << std::endl;
    }
    virtual void BuildComp2() override {
        std::cout << "\tAdvanceBuilder2 comp2" << std::endl;
    }
    virtual void BuildComp3() override {
        std::cout << "\tAdvanceBuilder2 comp3" << std::endl;
    }
};

/* test */
class Test {
public:
    Test(Builder *builder) : builder_(builder) {}

    Base *TestFuc() {
        builder_->BuildComp1();
        builder_->BuildComp2();
        builder_->BuildComp3();
        return builder_->GetBuild();
    }

private:
    Builder *builder_;
};
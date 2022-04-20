/**
 * @file Proxy.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-19
 * 
 * @copyright Copyright (c) 2022
 * 
 * 代理：封装被代理对象的接口，在前/后、或者直接对被代理对象方法进行修改
 * 
 */

#include <iostream>
#include <memory>

class ISubject {
public:
    virtual void Process() = 0;
    virtual ~ISubject() = default;
};

class SpecialSubject : public ISubject {
public:
    virtual void Process() override { 
        // 1...

        // 2...

        std::cout << "SpecialSubject: This is the way how SpecialSubject process." << std::endl;
    }
};

class ProxySpecialSubject : public ISubject {
public:
    virtual void Process() override {
        std::cout << "begin of special subject's proxy" << std::endl;

        // 1... there are some special or sophisticated steps in proxy than no-proxy

        // 2 call the original method or do some adding disposing;
        GetSpecialSubjectProxy().Process();

        // 3... there are some special or sophisticated steps in proxy than no-proxy

        std::cout << "end of special subject's proxy" << std::endl;

    }

protected:
    ISubject &GetSpecialSubjectProxy() {
        if (!p_) {
            p_ = std::make_unique<SpecialSubject>();
        }
        return *p_;
    }

private:
    std::unique_ptr<ISubject> p_;
};

int main() {
    std::unique_ptr<ISubject> proxy = std::make_unique<ProxySpecialSubject>();
    proxy->Process();

    return 0;
}
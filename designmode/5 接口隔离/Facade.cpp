/**
 * @file Facade.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-19
 * 
 * @copyright Copyright (c) 2022
 * 
 *  Facade 更多体现的是一种设计思维：系统内/外之间
 * 
 */

#include <iostream>

class Scanner {
public:
    void Scan() { std::cout << "Scan" << std::endl; }
};

class Parser { 
public:
    void Parse() {std::cout << "Parse" << std::endl; }
};

class CodeGenerator {
public:
    void GenerateCode() {std:: cout << "Generate Code" << std:: endl; }
};

class Compiler {
public:
    void run() {
        Scanner s;
        s.Scan();

        Parser p;
        p.Parse();

        CodeGenerator c;
        c.GenerateCode();
    }
};

/**
 * @brief main可以直接声明三个对象，分别调用，如果三个方法 的内部或者执行顺序需要改，那么main函数
 * 也需要改。现在的设计就不需要改main函数，Compiler提供了这个接口，也提高了这个接口的复用。
 * 
 * @return int 
 */
int main() {

    Compiler compiler;
    compiler.run();

    return 0;
}
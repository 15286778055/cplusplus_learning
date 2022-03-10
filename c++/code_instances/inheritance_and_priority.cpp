/*

    这个例子用来理解 继承 和 权限
    继承 和 组合 的作用很相似
    继承也可以看作组合，基类是一份，派生类是一份，派生类含有基类，
而基类对 自己成员 以及对 基类成员 可能会具有 public 、 private 、 protected 三种权限，
由public继承而来时，对基类成员， 1）public指明，派生类对象可以直接访问该成员；2）private指明，
派生类对象不可以直接访问；3）protected在两者之间


    例子中，使用 public 继承，基类的数据成员是 pricate 权限，派生类无法直接访问，但可以通过 public 权限
的基类方法来访问 private 权限的基类成员。按照以前的理解，应该“没有继承 private 成员”，基类的 private 成员
应当不存在，实际上，是存在的，只是 “访问权限” 级别不高而已，无法直接访问，但是通过 高权限的 public 基类方法，
照样可以访问这个 ：“看似不存在的 private 成员”。
    其实，继承，重要的是 给的 “访问权限” 的级别。
    在 Specia_s 的构造函数中，调用了 Student(arg1, arg2), 通过后面的 cout ，可以看出确实是 通过构造函数
初始化了基类的 private 成员。


    这么看，似乎语言也没有那么智能，有时候派生类用不到基类的private成员
    但是从 向上转型 派生类对象向基类对象转换来看，不管 派生类 对 基类 的成员是哪种访问权限，实际上，
派生类对象 都含有 基类对象。


    三个作用域：类内、类的派生类、类的用户
    类内可以自由访问，类内的 权限 指明了类的派生类、类的用户对类内的访问权限
    类的继承类型（派生访问说明符）指明了，派生类的派生类、派生类的用户对基类（继承来的权限）的访问权限，相当于一个buff叠加，它（派生访问说明符）只负责对继承过来的成员的权限的管理（一种叠加管理）

*/


#include <iostream>
#include <vector>
#include <cctype>
#include <initializer_list>
#include <typeinfo>

using namespace std;

class Student {

public:
    // Student() = default;

    Student(int arg1, int arg2) : grade(arg1), number(arg2) {}

    int get_number() const { return number; }

    int get_grade() const { return grade; }

private:
    int grade;
    int number;
    

};

class Special_s : protected Student {

public:

    // Special_s() = default;

    Special_s(int arg1, int arg2, int arg3) : Student(arg1, arg2), is_disordered(arg3) {}

    int get_is_disordered() const { return is_disordered; }

    void func() {
        cout << this->get_grade() << endl;
    }

    void func(int j) {
        cout << j << endl;
    }

protected:
    int is_disordered;

};

class Sspecial_s : public Special_s {
public:
    Sspecial_s(int arg1, int arg2, int arg3, int arg4) : Special_s(arg1, arg2, arg3), is_boy(arg4) {}

    // 这么写 应该就递归了，因为编译器应该首先找到的是自己的get_grade()，基类的
    // int get_grade() { return this->get_grade(); }
    int _get_grade() { return this->get_grade(); }
    int _get_number() { return this->get_number(); }


    // 覆盖了基类中的func()，从“名字查找先于类型检查”、“先内层，在外层”来看，在内层找到fun，却和func(arg)类型不匹配，所以为了使用基类的其他重载的func，必须使用using声明，
    // 一次性全部引入，或者全部重写（覆盖）
    using Special_s::func;
    void func() {
        cout << 200 << endl;
    }
    

private:
    int is_boy;

};

class A : private Student {
public:
    // 可以使用 using 改变继承而来的可访问的权限（可改变基类的非私有成员），如：基类的public、protected；而对基类的private，本就不具备访问权限，无法改变其在派生类的权限
    // 会报错
    // using Student::grade;

};


int main(int argc, char **argv) {

    Student s(9, 2);
    Special_s ss(10, 5, 0);
    Sspecial_s sss(15, 3, 1, 1);

    cout << s.get_grade() << endl;
    cout << s.get_number() << endl;

    
    cout << ss.get_is_disordered() << endl;

    ss.func();
    sss.func(100);
    sss.func();

    // Special_s protected继承了Student，所以Special_s的用户不能访问Student的方法，但是Special_s的派生类可以访问Special_s的public方法
    // 这里的SSpecial_s封装了对他来说是protected的Student的get_grade方法，封装成public，所以SSpecial_s的用户可以访问。
    // cout << ss.get_grade() << endl;
    // cout << ss.get_number() << endl;
    cout << sss._get_grade() << endl;
    cout << sss._get_number() << endl;

    cout << sizeof(Student) << endl;
    cout << sizeof(Special_s) << endl;
    cout << sizeof(s) << endl;
    cout << sizeof(ss) << endl;

    return 0;
}

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

class Special_s : public Student {

public:

    // Special_s() = default;

    Special_s(int arg1, int arg2, int arg3) : Student(arg1, arg2), is_disordered(arg3) {}

    int get_is_disordered() const { return is_disordered; }

    void func() {
        cout << this->get_grade() << endl;
    }

protected:
    int is_disordered;

};


int main(int argc, char **argv) {

    Student s(9, 2);
    Special_s ss(10, 5, 0);

    cout << s.get_grade() << endl;
    cout << s.get_number() << endl;

    cout << ss.get_grade() << endl;
    cout << ss.get_number() << endl;
    cout << ss.get_is_disordered() << endl;

    ss.func();

    cout << sizeof(Student) << endl;
    cout << sizeof(Special_s) << endl;
    cout << sizeof(s) << endl;
    cout << sizeof(ss) << endl;

    return 0;
}

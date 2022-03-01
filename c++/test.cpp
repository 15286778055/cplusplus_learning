#include <iostream>
#include <vector>
#include <cctype>
#include <initializer_list>

using namespace std;


class A {
public:
    A() {
        cout << "Class A is created." << endl;
    }

};

class B {
public:
    B() {
        cout << "Class B is created." << endl;
    }

};

class C : public A {
public:
    C() {
        cout << "Class C is created." << endl;
    }

private:
    B b;

};

 

void error_msg(initializer_list<int> il) {

    for (auto &elem : il) {
        cout << elem << endl;
    }

}

int get(int);

int main(int argc, char **argv) {

    // int a[] = {0, 1, 2};
    // cout << cbegin(a) + 3 << endl;
    // cout << cend(a) << endl;
    // cout << cend(a) - cbegin(a) << endl;

    const int &x = 0;
    // int &y = 9;
    int a = 3;
    int b[a];

   error_msg({0, 1, 2, 3});

   cout << get(109) << endl;
    
    const char e = 'a';
    char f = e;


    C c = C();

    cout << __cplusplus << endl;



    string str1 = "hello world";

    string str2 = str1;

      

    printf("Sharing the memory:/n");

    printf("/tstr1's address: %x/n", str1.c_str() );

    printf("/tstr2's address: %x/n", str2.c_str() );

      

    str1[1]='q';

    str2[1]='w';

 

    printf("After Copy-On-Write:/n");

    printf("/tstr1's address: %x/n", str1.c_str() );

    printf("/tstr2's address: %x/n", str2.c_str() );




    return 0;
}


int get(int i) {
    return i + 1;
}
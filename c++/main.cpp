#include <iostream>
#include <functional>
#include <type_traits>

using namespace std::placeholders;

typedef struct node NODE;

std::ostream& operator<< (std::ostream& os, const std::string& s);

void set(const int& i);
void set(const int i);

int main(int argc, char **argv) {


    if (argc == 2) {
        printf("%s\n", argv[1]);
        int i = argv[1][0] - '0';
        int j = argv[1][1] - '0';
        printf("%d\n", i);
        printf("%d\n", j);
    }

    std::cout << std::is_void<void>().value << std::endl;


    std::cout << std::string("get") << std::endl;

    const int i = 3;
    set(3);

    return 0;
}

std::ostream& operator<< (std::ostream& os, const std::string& s) {

    std::cout << "you get!" << std::endl;

    return os;
}
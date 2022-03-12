#include <iostream>
#include <functional>
#include <type_traits>

using namespace std::placeholders;

typedef struct node NODE;

int main(int argc, char **argv) {


    if (argc == 2) {
        printf("%s\n", argv[1]);
        int i = argv[1][0] - '0';
        int j = argv[1][1] - '0';
        printf("%d\n", i);
        printf("%d\n", j);
    }

    std::cout << std::is_void<void>().value << std::endl;

 

    return 0;
}
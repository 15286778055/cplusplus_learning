#include <stdio.h>
#include <stdlib.h>

typedef struct node NODE;

int main(int argc, char **argv) {


    if (argc == 2) {
        printf("%s\n", argv[1]);
        int i = argv[1][0] - '0';
        int j = argv[1][1] - '0';
        printf("%d\n", i);
        printf("%d\n", j);
    }

    

 

    return 0;
}
#include <iostream>
#include <cstring>
#include "Red_Black_Tree.hpp"
#include "Red_Black_Tree.cpp"


int main() {
    auto rbt = xp::RedBlackTree<int, std::string>();
    for (int i = 0; i < 100; ++i) {
        int j = rand()%100;
        std::cout << "j: " << j << std::endl;
        rbt.insert_element(j, "");
    }
    std::cout << "size: " << rbt.size() << std::endl;
    rbt.search_element_by_key(89);
    rbt.search_element_by_key(94);
    rbt.search_element_by_key(39);
    rbt.update_element(89, "xiaopeng");
    rbt.update_element(94, "xiaopeng");
    

    // rbt.insert_element(3, "33");
    // rbt.insert_element(1, "11");
    // rbt.insert_element(2, "22");
    // rbt._header->display();
    // rbt._header->child[0]->display();
    // rbt._header->child[1]->display();

    // rbt.insert_element(0, "00");

    // rbt.insert_element(-2, "-22");
    // rbt.insert_element(-1, "-11");
    // rbt.insert_element(-3, "-33");

    // rbt._header->display();
    // rbt._header->child[1]->display();
    // rbt._header->child[1]->child[0]->display();
    // rbt._header->child[0]->display();
    // rbt._header->child[0]->child[0]->display();
    // rbt._header->child[0]->child[0]->child[0]->display();
    // rbt._header->child[0]->child[0]->child[1]->display();


}
#include <iostream>
#include <cstring>
#include "Red_Black_Tree.hpp"
#include "Red_Black_Tree.cpp"


int main() {
    auto rbt = xp::RedBlackTree<int, std::string>();
    rbt.insert_element(3, "33");
    rbt.insert_element(2, "22");
    rbt.insert_element(1, "11");
    rbt._header->display();
    rbt._header->child[0]->display();
    rbt._header->child[1]->display();

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
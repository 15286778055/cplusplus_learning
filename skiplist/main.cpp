#include <cstring>

#include "SkipList.h"
#include "SkipList.cpp"

int main() {

    SkipList<int, std::string> skiplist(20);
    for (int i = 0; i < 20; ++i)
        skiplist.insert_element(i, std::to_string(i));

    // skiplist.insert_element(1, "222sdf");
    // skiplist.insert_element(4, "111sdsdfsf");
    // skiplist.insert_element(7, "666sdf");
    // skiplist.insert_element(4, "444sdsfsdff");
    skiplist.display_skiplist();
    skiplist.search_element_by_key(8);
    auto x = skiplist.search_element_by_key(4);
    if (x != nullptr)
        std::cout << "found, key: " << x->get_key() << " value: " << x->get_value() << std::endl;
    skiplist.update_element(4, "xiaopeng");
    skiplist.search_element_by_key(4);
    skiplist.update_element(100, "xiaopeng");
    skiplist.delete_element(4);
    skiplist.search_element_by_key(4);
    skiplist.display_skiplist();
    std::cout << "skip size: " << skiplist.size() << std::endl;
    skiplist.has_key(2);
    skiplist.has_key(100);

    skiplist.clear();
    skiplist.display_skiplist();

}
/* 跳表 */

#ifndef __SKIPLIST__
#define __SKIPLIST__

#include "SkipListNode.hpp"

template <typename Key, typename Value>
class SkipList {

public:


private:
    /* 跳表最大索引层数 */
    int _max_level;

    /* 当前节点索引层数 */
    int _skip_list_level;

    /* 指向头节点的指针*/
    Node<Key, Value>* _header;

    /* 跳表中元素数量 */
    int _element_count;

}









#endif
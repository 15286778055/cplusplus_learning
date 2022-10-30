/* 跳表 */

#ifndef __SKIP_LIST_H
#define __SKIP_LIST_H

#include <iostream>
// #include <fstream>
#include <string>
#include <ctime>
#include <random>

#include "SkipListNode.h"


template <typename Key, typename Value>
class SkipList {

public:
    /* 构造、析构函数 */
    SkipList(int max_level):_max_level(max_level), _skip_list_level(0), _element_count(0) {
        srand(time(nullptr));
        Key key;
        Value value;
        memset(&key, 0, sizeof(key));
        /* 生成默认节点，key 应当是 Key 类型中最小可取值 */
        this->_header = new SkipListNode<Key, Value>(key, value, max_level);
    }
    ~SkipList() { delete _header; }


public:
    /* 增删改查 */
    int insert_element(Key key, Value value);
    const SkipListNode<Key, Value>* search_element_by_key(Key key);
    int delete_element(Key key);
    int update_element(Key key, Value value);
    /* 清除跳表 */
    int clear();
    /* 是否含有某个键 */
    bool has_key(Key key);
    /* 获得新生成节点的随机索引层级 */
    int get_random_level();
    /* 跳表展示 */
    void display_skiplist();
    /* 跳表节点数、元素数量 */
    int size() const { return this->_element_count; }
    /* 读写文件 */
    int dump_file(std::string path, std::string name);
    int load_file(std::string path, std::string name);


private:
    /* 跳表最大索引层数 */
    int _max_level;

    /* 当前节点索引层数 */
    int _skip_list_level;

    /* 指向头节点的指针*/
    SkipListNode<Key, Value>* _header;

    /* 跳表中元素数量 */
    int _element_count;

    /* 读写文件描述符 */
    // std::ofstream _file_writer;
    // std::ifstream _file_reader;
};


#endif
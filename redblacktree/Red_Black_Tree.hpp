/* Red black tree */

#ifndef __RED_BLACK_TREE_HPP
#define __RED_BLACK_TREE_HPP

/* 命名空间 xp */
namespace xp {


/* 颜色 */
enum rbtnode_color { RED, BLACK };


/* 红黑树节点 */
template <typename Key, typename Value>
class RBTNode {

public:
    typedef Key key_type;       /* 键值类型别名 */
    typedef Value value_type;

public:
    /* 构造、析构函数 */
    RBTNode(key_type key, value_type value, rbtnode_color color = RED): key(key), value(value), color(color), l_child(nullptr), r_child(nullptr), parent(nullptr) {};
    /* 三根指针指向的区域不由当前节点分配，无需 delete */
    ~RBTNode() {}

public:
    /* getter setter */
    key_type get_key() { return key; }
    value_type get_value() { return key; }
    int set_value(value_type value) { this->value = value; }
    rbtnode_color get_node_color() { return color; }
    int set_node_color(rbtnode_color color) { this->color = color; }

public:
    RBTNode* l_child;    /* 左右子节点指针、 父节点指针 */
    RBTNode* r_child;
    RBTNode* parent;

private:
    key_type key;       /* 键值、节点颜色 */
    key_type value;
    rbtnode_color color;
};



/* 红黑树 */
template <typename Key, typename Value>
class RedBlackTree {

public:
    /* 键值类型别名 */
    typedef Key key_type;
    typedef Value value_type;

public:
    /* 构造、析构函数 */
    RedBlackTree(): element_count(0), _header(nullptr) {}
    /* 头指针指向的区域不由当前节点分配，无需 delete */
    ~RedBlackTree() {}
    
public:
    /* 增删改查 */
    int insert_element(key_type key, value_type value);
    int delete_element(key_type key);
    int update_element(key_type key, value_type value);
    RBTNode<key_type, value_type>* search_element_by_key(key_type key);
    /* 红黑树元素数量 */
    int size() { return element_count; }

public:
    RBTNode<key_type, value_type>* _header;       /* 头指针 */
    int element_count;      /* 元素数量 */

};



}


#endif
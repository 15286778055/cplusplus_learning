/* Red black tree realize*/
#include "Red_Black_Tree.hpp"


/* 命名空间 xp */
namespace xp {


/* 增 */
template <typename Key, typename Value>
int RedBlackTree<Key, Value>::insert_element(key_type key, value_type value) {
    /* 首先，找到插入位置 */
    RBTNode<Key, Value>* current = this->_header;

    /** case 1: 红黑树为空 
     * 插入的节点作为根节点
    */
    if (current == nullptr) {
        _header = new RBTNode<key_type, value_type>(key, value, BLACK);
        return 0;
    }

    /* case 2: 找到节点的位置 并插入 */
    RBTNode<Key, Value>* insert_node;
    while (current != nullptr) {
        // 键值已存在，报错返回 -1
        if (key == current->get_key()) {
            std::cerr << "Insert error, key exists." << std::endl;
            return -1;
        }
        if (key < current->get_key()) {
            if (current->child[0] != nullptr) current = current->child[0];
            else {
                current->child[0] = insert_node = new RBTNode<key_type, value_type>(key, value);
                current->child[0]->parent = current;
                break;
            }
        }
        if (key > current->get_key()) {
            if (current->child[1] != nullptr) current = current->child[1];
            else {
                current->child[1] = insert_node = new RBTNode<key_type, value_type>(key, value);
                current->child[1]->parent = current;
                break;
            }
        }
    }

    // 此时，current 为 新插入节点的父节点

    /* 父节点为 黑，插入成功 */
    if (current->get_node_color() == BLACK) return 0;

    /* 其他情况需要调整 */
    insert_adjust(current, insert_node);





}

/* 为了保持红黑树平衡特性，新节点插入的调整 */
template <typename Key, typename Value>
void RedBlackTree<Key, Value>::insert_adjust(RBTNode<key_type, value_type>* p, RBTNode<key_type, value_type>* n) {
    /* P 为红，U 为红 */

    /* P 为红，U为 nullptr */
    if (p->get_node_color() == RED) {
        // LL
        if (!which_child(p) && !which_child(n)) {
            // 右旋
            if (_header == p->parent) {
                _header = _header->child[0];
                _header->child[1] = _header->parent;
                _header->parent = nullptr;
                _header->child[1]->child[0] = nullptr;
                _header->child[1]->parent = _header;
            }
            else {
                p->parent->parent->child[which_child(p->parent)] = p;
                p->child[1] = p->parent;
                p->parent = p->parent->parent;
                p->child[1]->parent = p;
                p->child[1]->child[0] = nullptr;
                p->child[1]->child[1] = nullptr;
            }
            
            // 变色
            p->set_node_color(BLACK);
            p->child[1]->set_node_color(RED);
            return;
        }

        // RR
        if (which_child(p) && which_child(n)) {
            // 左旋
            if (_header == p->parent) {
                _header = _header->child[1];
                _header->child[0] = _header->parent;
                _header->parent = nullptr;
                _header->child[0]->child[1] = nullptr;
                _header->child[0]->parent = _header;
            }
            else {
                p->parent->parent->child[which_child(p->parent)] = p;
                p->child[0] = p->parent;
                p->parent = p->parent->parent;
                p->child[0]->parent = p;
                p->child[0]->child[1] = nullptr;
                p->child[0]->child[0] = nullptr;
            }
            // 变色
            p->set_node_color(BLACK);
            p->child[0]->set_node_color(RED);
            return;
        }

        // LR
        if (!which_child(p) && which_child(p)) {
            
        }

        // RL
        if (which_child(p) && which_child(n)) {
            
        }
    }
}

/* 工具：判断一个孩子是他爸爸的左孩子还是右孩子 */
template <typename Key, typename Value>
int RedBlackTree<Key, Value>::which_child(RBTNode<key_type, value_type>* node) {
    if (node->parent->child[0] == node) return L_CHILD;
    if (node->parent->child[1] == node) return R_CHILD;
    return -1;
}

/* 删 */
template <typename Key, typename Value>
int RedBlackTree<Key, Value>::delete_element(key_type key) {

}

/* 改 */
template <typename Key, typename Value>
int RedBlackTree<Key, Value>::update_element(key_type key, value_type value) {

}

/* 查 */
template <typename Key, typename Value>
RBTNode<Key, Value>* RedBlackTree<Key, Value>::search_element_by_key(key_type key) {

    

}




}
/* 命名空间 xp 结束 */
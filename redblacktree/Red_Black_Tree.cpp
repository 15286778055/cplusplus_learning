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
        ++element_count;
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
                ++element_count;
                break;
            }
        }
        if (key > current->get_key()) {
            if (current->child[1] != nullptr) current = current->child[1];
            else {
                current->child[1] = insert_node = new RBTNode<key_type, value_type>(key, value);
                current->child[1]->parent = current;
                ++element_count;
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
    
    /* 进入此情况，代表父节点为红，那么一定存在祖父节点 */
    lr_child u_index =  which_child(p) ? L_CHILD : R_CHILD;
    RBTNode<Key, Value>* g = p->parent;
    RBTNode<Key, Value>* u = g->child[u_index];
    if (u != nullptr && u->get_node_color() == RED) { /* recolor */
        /* P 为红，U 为红 */
        // 改变颜色
        p->set_node_color(BLACK);
        u->set_node_color(BLACK);
        p->parent->set_node_color(RED);
        // 如果 祖父节点是头节点，那么应当为黑色并返回
        if (p->parent == _header) {
            _header->set_node_color(BLACK);
            return;
        }

        // 祖宗节点为 红 时，需要把 G 当作 N 递归处理
        if (p->parent->parent != nullptr && p->parent->parent->get_node_color() == RED) insert_adjust(p->parent->parent, p->parent);
        else return;
    }
    else { /* rotate */
        /* P 为红，U为 nullptr 或 黑 */

        if (!which_child(p)) { /* p 是 g 的左孩子 LL或者LR */
            if (which_child(n)) { /* n 是 p 的右孩子 LR */
                /* 先左旋 */
                left_rotate(p);
                n = p;
                p = n->parent;
            }
            // 再右旋
            right_rotate(g);
            // 改变节点颜色
            auto tmp = p->get_node_color();
            p->set_node_color(g->get_node_color());
            g->set_node_color(tmp);
            return;
        }
        else { /* p 是 g 的右孩子 RR或者RL */
            if (!which_child(n)) { /* n 是 p 的左孩子 */
                // 先右旋
                right_rotate(p);
                n = p;
                p = n->parent;
            }
            // 再左旋
            left_rotate(g);
            // 改变节点颜色
            auto tmp = p->get_node_color();
            p->set_node_color(g->get_node_color());
            g->set_node_color(tmp);
            return;
        }
    }
}

/* ll rr lr rl 调整 */
template <typename Key, typename Value>
void RedBlackTree<Key, Value>::right_rotate(RBTNode<key_type, value_type>* n) {
    /* 右旋 */
    RBTNode<Key, Value>* n_left = n->child[0];
    n->child[0] = n_left->child[1];
    if (n->child[0] != nullptr) n->child[0]->parent = n;

    n_left->parent = n->parent;
    if (n->parent == nullptr) _header = n_left;
    else if (n == n->parent->child[0]) n->parent->child[0] = n_left;
    else if (n == n->parent->child[1]) n->parent->child[1] = n_left;

    n_left->child[1] = n;
    n->parent = n_left;
}

/* rr */
template <typename Key, typename Value>
void RedBlackTree<Key, Value>::left_rotate(RBTNode<key_type, value_type>* n) {
    /* 左旋 */
    RBTNode<Key, Value>* n_right = n->child[1];
    n->child[1] = n_right->child[0];
    if (n->child[1] != nullptr) n->child[1]->parent = n;

    n_right->parent = n->parent;
    if (n->parent == nullptr) _header = n_right;
    else if (n == n->parent->child[0]) n->parent->child[0] = n_right;
    else if (n == n->parent->child[1]) n->parent->child[1] = n_right;

    n_right->child[0] = n;
    n->parent = n_right;
}

/* 工具：判断一个孩子是他爸爸的左孩子还是右孩子 */
template <typename Key, typename Value>
int RedBlackTree<Key, Value>::which_child(RBTNode<key_type, value_type>* node) {
    if (node->parent->child[0] == node) return L_CHILD;
    if (node->parent->child[1] == node) return R_CHILD;
    return -1;
}

/* 工具：交换两个节点的 key value */
template <typename Key, typename Value>
void RedBlackTree<Key, Value>::exchange_node(RBTNode<key_type, value_type>* n1, RBTNode<key_type, value_type>* n2) {
    auto key = n1->get_key();
    auto value = n1->get_value();
    n1->set_key(n2->get_key());
    n1->set_value(n2->get_value());
    n2->set_key(key);
    n2->set_value(value);
}

/* 删 */
template <typename Key, typename Value>
int RedBlackTree<Key, Value>::delete_element(key_type key) {

    






}

/* 改 */
template <typename Key, typename Value>
int RedBlackTree<Key, Value>::update_element(key_type key, value_type value) {
    // 查找
    RBTNode<Key, Value>* current = _header;
    while (current != nullptr) {
        if (key == current->get_key()) {
            // 更新
            current->set_value(value);
            std::cout << "Update!  Key: " << current->get_key() << "  value: " << current->get_value() << "  color: " << current->get_node_color() << std::endl;
            return 0;
        }
        if (key < current->get_key()) current = current->child[0];
        if (key > current->get_key()) current = current->child[1];
    }
    // 更改
    std::cout << "Update unsuccessfully! Key not exists." << std::endl;
    return -1;
}

/* 查 */
template <typename Key, typename Value>
RBTNode<Key, Value>* RedBlackTree<Key, Value>::search_element_by_key(key_type key) {
    // 查找
    RBTNode<Key, Value>* current = _header;
    while (current != nullptr) {
        if (key == current->get_key()) {
            std::cout << "Found!  Key: " << current->get_key() << "  value: " << current->get_value() << "  color: " << current->get_node_color() << std::endl;
            return current;
        }
        if (key < current->get_key()) current = current->child[0];
        if (key > current->get_key()) current = current->child[1];
    }
    std::cout << "Found unsuccessfully!" << std::endl;
    return nullptr;

    // TODO: 我直接把指针返回了，仅仅是只读取的话，就还好，怕有其他操作
    // 后续如果升级为多线程服务，需要注意
    // 改为用 new 的话，需要由 new 的使用方去 delete

}




}
/* 命名空间 xp 结束 */
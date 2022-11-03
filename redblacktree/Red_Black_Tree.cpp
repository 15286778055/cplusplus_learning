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
    
    lr_child u_index =  which_child(p) ? L_CHILD : R_CHILD;
    RBTNode<Key, Value>* u = p->parent->child[u_index];
    if (u != nullptr && u->get_node_color() == RED) {
        // 改变颜色
        p->set_node_color(BLACK);
        u->set_node_color(BLACK);
        p->parent->set_node_color(RED);
        // 如果 祖父节点是头节点，那么应当为黑色
        if (p->parent == _header) _header->set_node_color(BLACK);

        // 祖宗节点为 红 时，需要把 G 当作 N 递归处理
        if (p->parent->parent != nullptr && p->parent->parent->get_node_color() == RED) insert_adjust(p->parent->parent, p->parent);
        else return;
    }
    else if (u == nullptr) {
        /* P 为红，U 为红 */
        if (p->get_node_color() == RED)

        /* P 为红，U为 nullptr */
        if (p->get_node_color() == RED) {
            // LL
            if (!which_child(p) && !which_child(n)) {
                insert_adjust_ll(p, n);
                return;
            }

            // RR
            if (which_child(p) && which_child(n)) {
                insert_adjust_rr(p, n);
                return;
            }

            // LR
            if (!which_child(p) && which_child(n)) {
                insert_adjust_lr(p, n);
                return;
            }

            // RL
            if (which_child(p) && !which_child(n)) {
                insert_adjust_rl(p, n);
                return;
            }
        }
    }
    
    
}

/* ll rr lr rl 调整 */
template <typename Key, typename Value>
void RedBlackTree<Key, Value>::insert_adjust_ll(RBTNode<key_type, value_type>* p, RBTNode<key_type, value_type>* n) {
    // 右旋
    // if (_header == p->parent) {
    //     _header = _header->child[0];
    //     _header->child[1] = _header->parent;
    //     _header->parent = nullptr;
    //     _header->child[1]->child[0] = nullptr;
    //     _header->child[1]->parent = _header;
    // }
    // else {
    //     p->parent->parent->child[which_child(p->parent)] = p;
    //     p->child[1] = p->parent;
    //     p->parent = p->parent->parent;
    //     p->child[1]->parent = p;
    //     p->child[1]->child[0] = nullptr;
    //     p->child[1]->child[1] = nullptr;
    // }
    // // 变色
    // p->set_node_color(BLACK);
    // p->child[1]->set_node_color(RED);
    
    // 创建新连接
    p->parent->child[1] = p->child[0];
    n->parent = p->parent;
    // 删除无效连接
    p->child[0] = nullptr;
    // 顺时针旋转节点
    Key temp_key = n->get_key();
    Value temp_value = n->get_value();
    n->set_key(n->parent->get_key());
    n->set_value(n->parent->get_value());
    n->parent->set_key(p->get_key());
    n->parent->set_value(p->get_value());
    p->set_key(temp_key);
    p->set_value(temp_value);
}

/* rr */
template <typename Key, typename Value>
void RedBlackTree<Key, Value>::insert_adjust_rr(RBTNode<key_type, value_type>* p, RBTNode<key_type, value_type>* n) {
    // 创建新连接
    p->parent->child[0] = p->child[1];
    n->parent = p->parent;
    // 删除无效连接
    p->child[1] = nullptr;
    // 逆时针旋转节点
    Key temp_key = n->get_key();
    Value temp_value = n->get_value();
    n->set_key(n->parent->get_key());
    n->set_value(n->parent->get_value());
    n->parent->set_key(p->get_key());
    n->parent->set_value(p->get_value());
    p->set_key(temp_key);
    p->set_value(temp_value);
}

/* lr */
template <typename Key, typename Value>
void RedBlackTree<Key, Value>::insert_adjust_lr(RBTNode<key_type, value_type>* p, RBTNode<key_type, value_type>* n) {
    /* 1 先左旋*/
    // 创建新连接
    p->child[0] = p->child[1];
    // 删除无效连接
    p->child[1] = nullptr;
    // 交换节点信息
    exchange_node(p, n);
    
    /* 2 再进行 ll 调整，右旋 */
    insert_adjust_ll(p, n);
}

/* rl */
template <typename Key, typename Value>
void RedBlackTree<Key, Value>::insert_adjust_rl(RBTNode<key_type, value_type>* p, RBTNode<key_type, value_type>* n) {
    /* 1 先右旋*/
    // 创建新连接
    p->child[1] = p->child[0];
    // 删除无效连接
    p->child[0] = nullptr;
    // 交换节点信息
    exchange_node(p, n);
    
    /* 2 再进行 ll 调整，右旋 */
    insert_adjust_rr(p, n);
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
/* 跳表节点 */


#ifndef __SKIPLISTNODE__
#define __SKIPLISTNODE__

#include <cstring>

/* 跳表节点中 键值对 的两个模板参数 */
template <typename Key, typename Value>
class SkipListNode {

public:
    /* 构造方法 */
    Node() {}
    Node(Key key, Value value, int level): key(key), value(value), node_level(level) {
        /* 维持节点的线性数组，长度为 level（索引层） + 1（原链表层），并赋 0 */
        this->forward = new Node<Key, Value>*[level+1];
        memset(this->forward, 0, sizeof(Node<Key, Value>*)*(level+1));
    }
    /* 析构函数 */
    ~Node() { delete []forward };

    /* getter setter */
    Key get_key() const { return this->key; }
    Value get_value const { return this->value; }
    void set_value(Value v) { this->value = v; }

private:
    /* 键值对 */
    Key key;
    Value value;
    /* 节点处于的层级 */
    int node_level;
    /* 维持节点的线性数组，长度为 level（索引层） + 1（原链表层），并赋 0
     * forward[0] 为 原链表层，forward[i] 为 第 i 索引层
     * 指向同层级下个节点的指针
     */
    Node<Key, Value>** forward;
}



#endif
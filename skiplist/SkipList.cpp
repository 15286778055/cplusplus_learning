/* skip list realize */
#include "SkipList.h"


/* 生成随机高度 */
template <typename Key, typename Value>
int SkipList<Key, Value>::get_random_level() {
    int k = 0;
    while (k < _max_level) {
        if (rand() % 2 == 0) break;
        ++k;
    }
    return k;
}

/* 打印跳表 */
template <typename Key, typename Value>
void SkipList<Key, Value>::display_skiplist() {
    std::cout << "Show Skip List ------------------------- " << std::endl;
    
    /* 跳表为空 */
    if (_element_count == 0) {
        std::cout << "Skip list has no elements!" << std::endl;
        std::cout << "Show Skip List ------------------------- " << std::endl;
        return;
    }
    
    /* 从最高层开始便利 */
    SkipListNode<Key, Value>* current;
    for (int i = _skip_list_level; i >= 0; --i) {
        if (i != 0) std::cout << "index level " << i << ":";
        else std::cout << "original list:";
        current = _header->forward[i];
        while (current) {
            std::cout << "\tkey: " << current->get_key();
            current = current->forward[i];
        }
        std::cout << std::endl;
    }
    std::cout << "Show Skip List ------------------------- " << std::endl;
}

/* 增 */
template <typename Key, typename Value>
int SkipList<Key, Value>::insert_element(Key key, Value value) {

    /* 1 找到要插入的位置，并记录下路径，插入时需要改变新节点附近路径 */
    SkipListNode<Key, Value>* current = this->_header;
    /* 选择 _max_level+1 避免新生成的节点的层级高于 _skip_list_level*/
    SkipListNode<Key, Value>* update[_max_level+1];
    memset(update, 0, sizeof(SkipListNode<Key, Value>*)*(_max_level+1));

    /* 从当前最高索引层开始寻找插入点 */
    /* 对于特殊类的比较，可以重载操作符 */
    for (int i = _skip_list_level; i >= 0; --i) {
        while (current->forward[i] != nullptr && current->forward[i]->get_key() < key)
            current = current->forward[i];
        /* 更新路径节点信息 */
        update[i] = current;
    }

    /* current 走向待插入位置的下一个节点，该节点需要与 待插入的 key 作比较，有可能与 key 相等 */
    current = current->forward[0];
    if (current != nullptr && current->get_key() == key) {
        std::cout << "Key: " << key << ", exists" << std::endl;
        return -1;
    }
    

    /* 2 插入节点 */
    /* 待插入位置的下个节点为空 或者 键 不等于 待插入的 key，此两种情况需要插入节点 */
    if (current == nullptr || current->get_key() != key) {
        // 生成索引层级
        int random_level = get_random_level();

        // 新节点索引层级高于跳表当前索引层级，需要更新跳表索引
        if (random_level > _skip_list_level) {
            for (int i = _skip_list_level+1; i <= random_level; ++i)
                update[i] = _header;
            _skip_list_level = random_level;
        }
            

        // 生成节点
        SkipListNode<Key, Value>* inserted_node = new SkipListNode<Key, Value>(key, value, random_level);

        // 插入节点，虽然有 random_level+1 根指针，但是这些指针，全指向 同一个节点，已经是最节省空间的跳表实现方式了
        for (int i = random_level; i >= 0; --i) {
            inserted_node->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = inserted_node;
        }
        std::cout << "Insert successfully! "  << " key: " << key << "  Value: " << value << std::endl;
        ++_element_count;
    }
    return 0;
}

/* 查 */
template <typename Key, typename Value>
const SkipListNode<Key, Value>* SkipList<Key, Value>::search_element_by_key(Key key) {
    SkipListNode<Key, Value>* current = _header;
    
    /* 查找 */
    for (int i = _skip_list_level; i >= 0; --i) {
        while (current->forward[i] != nullptr && current->forward[i]->get_key() < key)
            current = current->forward[i];
        // current 走到第 i 层的倒数第二个节点，比较下个节点是否就是要找的节点，避免找到最底层
        if (current->forward[i] != nullptr && current->forward[i]->get_key() == key) {
            std::cout << "Found successfully! key: " << key << "  value:" << current->forward[i]->get_value() << std::endl;
            return current->forward[i];
        }
    }
    std::cout << "Found unsuccessfully! key: " << key << " does't not exists" << std::endl;
    return nullptr;
}

/* 改 */
template <typename Key, typename Value>
int SkipList<Key, Value>::update_element(Key key, Value value) {
    /* 首先，找到需要更改的节点 */
    SkipListNode<Key, Value>* current = _header;
    /* 逐层 由上至下 由左往右 遍历*/
    for (int i = _skip_list_level; i >= 0; --i) {
        while (current->forward[i] != nullptr && current->forward[i]->get_key() < key)
            current = current->forward[i];
        
        /* 每一层的最后，比较下一个节点与需要更改节点的关系，如果对比上，不用去往更底层索引，甚至链表 */
        if (current->forward[i] != nullptr && current->forward[i]->get_key() == key) {
            // 当前层最后一个节点就是我们想要更改的节点
            // 修改
            current->forward[i]->set_value(value);
            std::cout << "Update successfully!  key: " << key << " value: " << value << std::endl;
            return 0;
        }
    }
    std::cout << "Update unsuccessfully!  The key:" << key << " does't exist"  << std::endl;
    return -1;
}

/* 删 */
template <typename Key, typename Value>
int SkipList<Key, Value>::delete_element(Key key) {
    /* 首先，找到需要删除的节点，并保存中间的更新信息 */
    SkipListNode<Key, Value>* current = _header;
    SkipListNode<Key, Value>* update[_skip_list_level+1];

    /* 逐层，由左到右，由上至下 遍历*/
    for (int i = _skip_list_level; i >= 0; --i) {
        while (current->forward[i] != nullptr && current->forward[i]->get_key() < key)
            current = current->forward[i];
        update[i] = current;
    }

    /* current（现处于最底层）的下个节点是否为想要删除的节点 */
    current = current->forward[0];
    // 想要删除的节点不存在
    if (current == nullptr || current->get_key() != key) {
        std::cout << "Delete unsuccessfully!  Key: " << key << " does's not exist." << std::endl;
        return -1;
    }
    // 想要删除的节点存在
    if (current != nullptr && current->get_key() == key) {
        // 更新节点信息 删除节点
        for (int i = current->get_node_level(); i >=0; --i)
            update[i]->forward[i] = current->forward[i];
        // 更新跳表的层级;
        while (_skip_list_level > 0 && _header->forward[_skip_list_level] == nullptr)
            --_skip_list_level;
        
        std::cout << "Delete successfully!  key:" << key << "  value: " << current->get_value() << std::endl;
        // 删除动态分配的节点
        delete current;
        // 成员数量减一
        --_element_count;
        return 0;
    }
    return -1;
}

/* 是否含有某个键 */
template <typename Key, typename Value>
bool SkipList<Key, Value>::has_key(Key key) {
    SkipListNode<Key, Value>* current = _header;
    
    /* 查找 */
    for (int i = _skip_list_level; i >= 0; --i) {
        while (current->forward[i] != nullptr && current->forward[i]->get_key() < key)
            current = current->forward[i];
        // current 走到第 i 层的倒数第二个节点，比较下个节点是否就是要找的节点，避免找到最底层
        if (current->forward[i] != nullptr && current->forward[i]->get_key() == key) {
            std::cout << "Found successfully! key: " << key << std::endl;
            return true;
        }
    }
    std::cout << "Found unsuccessfully! key: " << key << " does't not exists" << std::endl;
    return false;
}

/* 删除跳表 */
template <typename Key, typename Value>
int SkipList<Key, Value>::clear() {
    /* 删除 header 索引层所有指针 */
    for (int i = _skip_list_level; i > 0; --i)
        _header->forward[i] = nullptr;
    _skip_list_level = 0;

    /* 删除底层链表 */
    SkipListNode<Key, Value>* current = _header->forward[0];
    _header->forward[0] = nullptr;
    while (current != nullptr) {
        auto deleted = current;
        current = current->forward[0];
        delete deleted;
    }
    _element_count = 0;
    std::cout << "Clear successfully!" << std::endl;
    return 0;
}


/**
 * 写到文件的方式：以 key: value 的形式 按行保存到文件
 * 从文件读的方式：按行读取，并且重新 insert_element 构建跳表，整个跳表结构不保证和原先一致
*/
/* 写文件 */
template <typename Key, typename Value>
int SkipList<Key, Value>::dump_file(std::string path) {
    std::cout << "Dump file start, path: " << path << std::endl;
    
    /* 打开文件 */
    _file_writer.open(path);
    SkipListNode<Key, Value>* current = _header->forward[0];

    /* 遍历链表层节点 */
    while (current != nullptr) {
        // 写文件
        _file_writer << current->get_key() << delimiter << current->get_value() << "\n";

        // 循环
        current = current->forward[0];
    }
    
    /* 刷新缓冲，关闭文件 */
    _file_writer.flush();
    _file_writer.close();
    std::cout << "Dump File successfully!" << std::endl;
    return 0;

}

/* 读文件 */
template <typename Key, typename Value>
int SkipList<Key, Value>::load_file(std::string path) {
    std::cout << "Load file start, path: " << path << std::endl;

    /* 打开文件 */
    _file_reader.open(path);

    /* 逐行读取并构建跳表 */
    std::string line;
    std::string* key = new std::string();
    std::string* value = new std::string();
    while (getline(_file_reader, line)) {
        /* 解析 key value */
        get_key_value_from_string(line, key, value);
        
        if (key->empty() || value->empty()) continue;
        
        /* 插入节点 重新构建跳表 */
        insert_element(static_cast<key_type>(*key), static_cast<value_type>(*value));
    }
    std::cout << "Load file successfully!" << std::endl;
    delete key;
    delete value;
    _file_reader.close();
    return 0;
}

/* 从 key:value 中分离 key 和 value */
template <typename Key, typename Value>
void SkipList<Key, Value>::get_key_value_from_string(const std::string& str, std::string* key, std::string* value) {
    /* 检测 key:value 字符串合法性*/
    if (is_valid_string(str)) return;

    *key = str.substr(0, str.find(delimiter));
    *value = str.substr(str.find(delimiter)+1, str.length());
}

/* 检测字符串是否满足 key:value 的要求*/
template <typename Key, typename Value>
bool SkipList<Key, Value>::is_valid_string(const std::string& str) {
    if (str.empty()) return false;
    if (str.find(delimiter) == std::string::npos) return false;
    return true;
}
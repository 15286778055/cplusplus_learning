

# c++ 体系结构与内核分析


- level 0：使用c++标准库
- level 1：认识c++标准库
- level 2：良好使用c++标准库
- level 3：扩充c++标准库


## 1 认识 headers 、版本、重要资源


c++标准库 > STL（标准模板库）


新式 headers 内的组件封装于 namespace "std"







## 2 STL体系结构基础介绍

#### STL 六大部件

- 容器（containers）
- 分配器（Allocators）
- 算法（Algorithms）
- 迭代器Iterators）
- 适配器（Adapters）
- 仿函式（Functors）



#### 六大部件使用示例

```c++
int main() {

    int ia[6] = {27, 210, 12, 47, 109, 83};
    vector<int, allocator<int>> vi(ia, ia+6);

    cout << cout_if(vi.begin(), vi.end(), not1(bind2nd(less<int>(), 40)))
}
```


#### `前闭后开`区间 `[  )`








## 3 容器分类与各种测试（一）


- 序列容器
  - Array
  - Vector
  - Deque
  - List
  - Forward-List
  - string
- 关联容器（红黑树）
  - set/multiset
  - map/multimap
  - unordered set/multiset （HashTable Separate Chaining）
  - unordered map/multimap


#### 容器种类图示

![3-1](pic/stl/3-1.png)

#### 无序容器实现（怎么感觉跟 `桶排序` 有点像） `Separate Chaining`
![3-1](pic/stl/3-2.png)







## 4 容器分类与各种测试（二）

vector 成长是 按两倍成长

可能造成内存浪费


## 5 容器分类与各种测试（三）


![5-1 deque](pic/stl/5-1%20deque实现.png)


#### `stack` 和 `queue` 使用 `deque` ，且无iterator



## 6 容器分类与各种测试（四）

- 关联容器（红黑树）
  - set/multiset
  - map/multimap
  - unordered set/multiset （HashTable Separate Chaining）
  - unordered map/multimap

#### 关联容器查找很快

#### 无序容器中 `元素` 大于 `篮子` 时， `篮子` 扩充两倍







## 7 使用分配器 `allocator` ：支持容器对内存的使用

#### allocator 使用，不建议使用，不好用
- allocate(x)
- deallocate(T* p, x)





## 8 源代码之分布（VG、GCC）

#### gnu 2.9.1






## 9 OOP vs GP （范型编程）

#### GP：Generic Programming

#### - OOP：数据和算法关联一起
#### - GP：将data与methods分开






## 10 操作符重载 & 模板









# 第二节

## 11 分配器


#### VC6 <xmemory>
##### allocators
- allocate：allocate ---> operator new ---> alloc
- deallocate：deallocate ---> operator delete ---> free


#### GNU2.9 <defalloc.h>
##### allocators
- allocate：allocate ---> operator new ---> alloc
- deallocate：deallocate ---> operator delete ---> free

#### 是同 VC6


#### **使用 malloc 和 free 来管理内存，会带来大量额外开销，现实中区块小，额外开销占比大**

#### 如右下角说明，GNU C 虽然实现了，但并未使用这个allocator，而是另有实现

![11-1](pic/stl/11-1.png)

#### 实际使用 `alloc` 为了减少额外开销，所以要减少 malloc 次数
![11-2](pic/stl/11-2.png)


#### alloc 实现
#### 16个指针 分别对应 8 2*8 3*8 ... 16*8字节的空间
![11-3](pic/stl/11-3%20alloc.png)


#### gnu4.5以后已改回最基础的实现





## 12 容器之间的实现关系与分类

#### 关系图
![12-1](pic/stl/12-1.png)








## 13 深度探索list（上）

#### 结构
![13-1](pic/stl/13-1.png)

- 迭代器：智能指针、大量操作符重载


#### 智能指针 `*` `->` 操作符重载
###### `->` 操作符重载有注意事项 
![13-2](pic/stl/13-2.png)




## 14 深度探索list（下）

#### 新版本4.9的改动

代码更简洁、合理








## 迭代器的设计原则、iterator traits

#### iterator 需要遵循的原则
#### iterator associated type
 - iterator_category
 - difference_type
 - value_type
 - reference（c++标准库未使用）
 - pointer（c++标准库未使用）

```c++
template<class T, class Ref, class Ptr>
struct __list_iterator
{
  typedef bidirectional_iterator_tag iterator_categoty;
  typedef T value_type;
  typedef Ptr pointer;
  typedef Ref reference;
  typedef ptrdiff_t difference_type;
}
```


### traits
#### Iterator Traits 用以分离 class iterators 和no-class iterators（native pointer）

#### 偏特化实现 Iterator Traits
![15-1](pic/stl/15-1.png)

![15-2](pic/stl/15-2.png)







## 16 vector深度探索

三根指针（iterator） GNU2.9 12个字节， GNU4.9 24个字节
- start
- finish
- end_of_storage

连续开辟空间提供 `[]` 操作符

#### 结构
![16-1](pic/stl/16-1.png)

#### push_back 函数
![16-2](pic/stl/16-2.png)

![16-3](pic/stl/16-3.png)

##### 以上大量调用拷贝构造函数和析构函数

#### G2.9 vector‘s iterator
![16-4](pic/stl/16-4.png)


#### G2.9 vector 是连续存储空间，其 iterator 是一个指针，而不是一个 class ，利用到 traits 获取iterator 应当定义的类型

#### G4.9 vector‘s iterator
![16-5](pic/stl/16-5.png)

![16-6](pic/stl/16-6.png)

#### 疑问？iterator 写成类模版，或者写成 traits 类模版，不都是类模版吗，或者与开销有关？？？










## 17 array 、 forward_list

#### TR1
![17-1](pic/stl/17-1.png)

#### G4.9
![17-2](pic/stl/17-2.png)

#### forward_list
![17-3](pic/stl/17-3.png)








## 18 deque 、 queue 、 stack（上）

#### deque 结构
![18-1](pic/stl/18-1.png)

#### deque 源码
- iterator start;
- iterator finish;
- map_pointer map;  // 是一个 T**
- size_type map_size;  // 指的是单个存储区的大小
![18-2](pic/stl/18-2.png)

#### iterator
- T* cur;
- T* first;
- T* last;
- map_pointer node; 是一个 T**
![18-3](pic/stl/18-3.png)

#### deque<T>::insert()
![18-4-1](pic/stl/18-4-1.png)
##### insert_aux, 判断怎么移动开销最小，并逐个移动
![18-4-2](pic/stl/18-4-2.png)




## 19 deque 、 queue 、 stack（下）

#### deque 如何模拟连续空间


#### deque 扩展时，因为时 vector 实现的，依然会成 2 倍扩展，但是为了满足前后进队，所以扩充复制的时候，会复制到新空间的中段






# 关联式容器
- 红黑树
- 散列表


## 20 RB-Tree 红黑树

#### 一种平衡二分搜索树


#### 第三个 typename 是实现仿函数，重载 operator() ，但底层怎么用的不清楚  g2.91里面就是 identity() 函数








## 21 set、multiset


### 一种 container adapter

#### set 借由 const_iterator 无法改变key








## 22 map、multimap

#### map 借由 cosnt Key , 无法改变key









## 23 hashtable 上


#### 元素个数大于篮子个数，就需要 rehashing 
#### gnu c2.9 中 由素数 53 开始，扩充时找 106 = 53 * 2 附近的素数

![23-1](pic/stl/23-1.png)





## 24 hashtable 下

#### 模版中 大多数为仿函数对象  function-like class
- hash 仿函数
- compare 仿函数
- ExtractKey 仿函数






## unordered_container

## 25 26 hash_set hash_multiset hash_map hash_multimap



![25-1](pic/stl/25-1.png)

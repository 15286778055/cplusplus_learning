

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






## 算法

## 27 算法的形式

#### 仿函数、迭代器、适配器使用类模版的原因，而不是单个单数的原因，或许是为了适配GP编程

![27-1](pic/stl/27-1.png)






## 28 迭代器分类

- struct input_iterator_tag {};
- struct output_iterator_tag {};
- struct forward_iterator_tat: public input_iterator_tag {};
- struct bidirectional_iterator_tag: public forward_iterator_tag {};
- struct random_access_iterator_tag: public bidirectional_iterator_tag {};






## 29 迭代器分类对算法的影响


#### 算法效率与判断迭代器类型有很大关系





## 30 算法源代码剖析（11个例子）


#### 1 accumulate

##### 两个版本

```c++
// 版本一
template<class InputIterator, class T>
T accumulate(InputIterator first, InputIterator last, T init)
{
  for (; first != last; ++first)
    init = init + *first;
  return init;
}

// 版本二，接收特定的 accumalate 操作的函数
template<class InputIterator, class T, class BinaryOperation>
T accumulate(InputIterator first, InputIterator last, T init, BinaryOperation binary_op)
{
  for ( ; first != last; ++first)
    init = binary_op(init, *first);
  return init;
}
```

#### 例子里面 那个函数式的操作，可以传入：
- 函数
- 仿函数的对象（仿函数）

# 那么 `函数` `仿函数` 具体区别在哪

![30-1](pic/stl/30-1.png)






#### 2 for_each

```c++
template<class InputIterator, class Function>
Function for_each(InputIterator first, InputIterator last, Function f)
{
  for ( ; first != last; ++first)
    f(*first);
  return f;
}
```





#### 3 replace replace_if replace_copy

![30-2](pic/stl/30-2.png)





#### 4 count count_if

##### 注意自带有 count 函数的容器

![30-3](pic/stl/30-3.png)





#### 5 find find_if

##### 注意自带有 find 函数的容器

![30-4](pic/stl/30-4.png)




#### 6 sort

![30-5](pic/stl/30-5.png)




#### 关于 reverse iterator , rbegin(), rend()

##### iterator adapter

##### *但是，这个反向迭代器需要++，那么应该需要对 reverse iterator 重载 `++` ，调用一般 iterator中的 `--` ，应该即可*

![30-6](pic/stl/30-6.png)




#### 7 binary_search

![30-7](pic/stl/30-7.png)






## 31 仿函数 functors 、函数对象

### function-like class ，重载 `operator()`

### `函数` 与 `仿函数` 的区别，为什么要有 `仿函数`


#### stl 中自带的 仿函数
![31-1](pic/stl/31-1.png)




#### G2.9 非c++标准的 仿函数
![31-2](pic/stl/31-2.png)




#### 函数对象、仿函数都可以实现的功能。自实现的 仿函数 也可以不继承 unary_function binary_function

#### “体系” 的观念
![31-3](pic/stl/31-3.png)




#### 仿函数 可适配 的条件
- 继承 unary_function
- 继承 binary_function
##### 两者中有 typedef 类型名

![31-4](pic/stl/31-4.png)


### 后续回答
### 为什么要继承 unary_function binary_function ??








## 32 adapter

#### 改造器，针对 XX 做出修改，接口调整

#### 为了满足一些接口、实现一些功能，针对已有的对象，所做出的调整
#### 如：queue、stack，基于deque做出调整

- container adapter
- iterator adapter
- function adapter

#### 实现一个已有功能的方式
- 继承
- 内含（composition）

#### Adapter 实现方式：`composition`







## 33 Binder2nd

#### 辅助函数价值：*函数模版可以做实参类型推导*


![33-1](pic/stl/33-1.png)



#### 1 问答式，避免 runtime error
传递两个参数的地方 40，*first
严格的，40两个传递的地方都指明了应该是的类型


#### 2 对应 31中的 仿函数 可适配 的条件。回答了31种最后问的问题，为什么要继承 unary_function binary_function ??
- 继承 unary_function
- 继承 binary_function
##### 两者中有 typedef 类型名



#### 3 为了作为其他适配器的参数，binder2nd又继承了unary_function



#### 4 问个问题，不这么用行不行？？？











## 34 not1

同上









## 35 新适配器 bind

![35-1](pic/stl/35-1.png)

![35-2](pic/stl/35-2.png)

![35-3](pic/stl/35-3.png)







## *迭代器适配器*

## 36 迭代器适配器：reverse_iterator

##### 实现
![36-1](pic/stl/36-1.png)






## 37 迭代器适配器：inserter

##### 思想：就是为了改变copy中的 `operator=` 操作符的作用，需要对这个做出重载。辅助函数帮助返回一个新的迭代器对象，替换原本应该返回的迭代器对象，然后对这个 `insert_iterator` 迭代器重载 `operator=` 操作符，完成操作

![37-1](pic/stl/37-1.png)






## *x适配器*

## 38 ostream_~~iterator~~

##### 这里严格来说，也不算是迭代器，完全忽略了迭代器指针的操作，也是针对 copy函数 中的操作，去重载这些操作符，完成ostream的操作

![38-1](pic/stl/38-1.png)





## 39 istream_~~iterator~~

![39-1](pic/stl/39-1.png)

![39-2](pic/stl/39-2.png)





## 32-39 适配器总结

#### 容器适配器
###### 比如 stack、queue 使用了 deque，实现方式为 composition，如果是继承，相当于对所有接口都开放了，不利于原来的封装

#### 函数适配器
###### 本质是实现另一个版本的 `函数对象（仿函数）` 
- 实现类模版的 `operator()`
- 辅助函数：利用辅助函数的实参类型推导，传递给对应的类模版

#### 迭代器适配器
###### 本质是实现另一个版本的 `迭代器` 模版
- 需要重载对应的 `操作符、函数` 
- 看情况是否需要辅助函数






## 第四讲 标准库中非STL部分

## 40 一个万用的 hash function

#### 实现便特化的方式
- 1、2    类模版重载 `operator()` 

![40-1](pic/stl/40-1.png)

- 3 struct hash 便特化

![40-2](pic/stl/40-2.png)


#### hash

![40-3](pic/stl/40-3.png)







## 41 tuple

#### tuple 使用
![41-1](pic/stl/41-1.png)

#### tyuple 实现方式：递归继承
![41-2](pic/stl/41-2.png)






## 42 type traits

## 头文件 <type_traits>

#### type traits 使用
![42-1](pic/stl/42-1.png)




## 43 type traits 实现

#### is_void 实现
![43-1](pic/stl/43-1.png)

#### is_integral 实现
![43-2](pic/stl/43-2.png)

#### 找不到代码，由编译器实现部分
![43-3](pic/stl/43-3.png)


### q: *有个问题，那种获取 type trais 没有声明对象，怎么获取的？*
### a: 看了源码，那个value是一个静态变量，所以可以直接 is_void<void>::value 访问






## 44 cout

#### *重载*





## 45 movable 元素对于 `容器` 速度效能的影响

- 浅拷贝
```c++
class MyString {

private:
  char* _data;
  size_t _len;

public:
  // 移动拷贝构造
  // 构造函数的初始值列表执行 “浅拷贝”
  // 函数内部将指针指向NULL，避免同时两个指针指向一块地址
  MyString(MyString&& str): _data(str._data), _len(str._len) {
    str._len = 0;
    str._data = NULL;
  }

  // 移动赋值构造
  MyString& operator=(MyString&& str) noexcept {
    if (this != &str) {
      if (_data) delete _data;
      _len = str._len;
      _data = str._data;
      str._len = 0;
      str._data = NULL;  // 避免delete(in dtor)
    }
    return *this;
  }

}

// 如果 MyString 作为 unrodered container 的对象，还需要实现 hash
namespace std
{
//偏特化的hash
template<>
struct hash<MyString> {
  size_t operator()(const MyString& s) const noexcept {
    // 调用 string 的 hash
    return hash<string>()(string(s.get()));
  }
}
}

// 使用
M c11(c1);
M c12(std::move(c1));
```
- 深拷贝

#### COW（copy on write）写时复制


## 46 测试









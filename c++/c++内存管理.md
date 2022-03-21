
# c++内存管理

- 第一讲：primitives
- 第二讲：malloc/free
- 第三讲：std::allocator
- 第四讲：other allocator
- 第五讲：loko::allocator




## 1 overview






## 2 内存分配的每一层面

![2-1](pic/memory/2-1.png)

![2-2](pic/memory/2-2.png)


## 3 四个层面的基本用法

```c++
// 1 malloc free
void* p1 = malloc(512);
free(p1);

// 2 new delete 表达式
complex<int>* p2 = new complex<int>;
delete p2;

// 3 operator new()   operator delete()
void* p3 = ::operator new(512);
::operator delete(p3);

// 4 stl 的 allocator
// 三个版本

#ifdef _MSC_VER
    // 分配3个int
    int* p4 = allocator<int>().allocate(3, (int*)0);
    allocator<int>().deallocate(p4, 3);
#endif
#ifdef _BORLANDC
    // 分配5个int
    int* p4 = allocator<int>().allocate(5);
    allocator<int>().deallocate(p4, 5);
#endif
#ifdef __GNUC__
    // 分配512bytes
    void* p4 = alloc::allocate(512);
    alloc::deallocate(p4, 512)
#endif
// GNUC另外的版本
#ifdef __GNUC__
    // 分配7个int
    void* p4 = allocator<int>().allocate(7);
    allocator<int>().deallocate((int*)p4, 7)
```





## 4 5 6 new expression / delete expression

#### new expression
##### new --> operator new ---> malloc
```c++
Complex* pc = new Complex(1, 2);
// 相当于
Complex* pc;
try {
    // 开辟内存
    void* mem = operator new(sizeof(Complex));
    pc = static_const<Complex*>(mem);
    // 创建对象
    pc->Complex::Complex(1,2);
} catch (std::bad_alloc) {
    // 若allocation失败就不执行constructor
}
```
![4-1](pic/memory/4-1.png)


#### delete expression
##### delete ---> 析构 & operator delete ---> free()
```c++
Complex* pc = new Complex(1, 2);
...
delete pc;

// 相当于
pc->~Complex();
operator delete(pc);
```
![5-1](pic/memory/5-1.png)


#### Ctor 不能由对象直接调用，但有的编译器版本可以这么做，这么做不严谨







## 7 array new & array delete

#### 应当配合使用，new 搭配 delete，array new 搭配 array delete
#### array delete 会调用相当次数的 `析构函数` ，避免内存泄露（成员指针指向的内存）





## 8 placement new ，定点new

```c++
#include <new>
char* buf = new char[sizeof(Complex)*3];
Complex* pc = new(buf)Complex(1,2);
...
delete[] buff;

// 编译器转为
Complex *pc;
try {
    void *m = operator new(sizeof(Complex), buf);
    pc = static_const<Complex*>(mem);
    pc->Complex::Complex(1,2);
} catch (std::bad_alloc) {
    // 若allocation失败就不执行constructor
}
```

#### placement new 指的是 new(p) 或 有参数的 ::operator new(size, void*)

![8-1](pic/memory/8-1.png)








## 9 重载

#### c++应用程序分配内存
![9-1](pic/memory/9-1.png)

#### c++容器分配内存
![9-2](pic/memory/9-2.png)

### *三把刀 如何接管内存分配，做内存池*
#### ::operator new & delete
![9-3](pic/memory/9-3.png)

#### operator new & delete
![9-4](pic/memory/9-4.png)

#### operator new[] & delete[]
![9-5](pic/memory/9-5.png)





## 10 11 重载示例

![10-1](pic/memory/10-1.png)
![10-3](pic/memory/10-3.png)
![10-3](pic/memory/10-3.png)




## 12 per-class allocator 一个类对应一个allocator

#### 重载 operator new & delete ，避免多次malloc

```c++
#include <cstddef>
#include <iostream>
using namespace std;

class Screen {
public:
    Screen(int x): i(x) {}
    int get() { return i; }
    // 重载
    void* operator new(size_t);
    void operator delete(void*, size_t);

private:
    int i;
    Screen *next;
    static Screen *freeStore;
    static const int screenChunk;
};
// 类内静态变量再次声明，为什么？？
Screen* Screen::freeStore = 0;
const int Screen::screenChunk = 24;

void* Screen::operator new(size_t size) {
    Screen *p;
    if (!freeStore) {
        // linked list 是空的，所以申请一大截
        size_t chunk = screenChunk * size;
        freeStore = p = reinterpret_cast<Screen*>(new char[chunk]);
        // 将一大块分割成片，当作 linked list 串接起来
        for (; p != &freeStore[screenChunk - 1]; ++p)
            p->next = p + 1;
        p->next = 0;
    }
    p = freeStore;
    freeStore = freeStore->next;
    return p;
}

void Screen::operator delete(void *p, size_t) {
    // 将 deleted object 插回 free list 前端
    (static_cast<Screen*>(p))->next = freeStore;
    freeStore = static_cast<Screen*>(p);
}
```




## 13 per-class allocator2 一个类对应一个allocator的改进

#### 将 数据 与 next指针 组合成结构体，避免 next指针 对内存的消耗
#### 当未将已经分配的内存给到 新的指针时，使用 next指针 串联分配的整块内存空间，使用联合体有效解决


```c++
using namespace std;
class Airplane {
public:
    unsigned long getMiles() { return miles; }
    char getType() { return type; }
    void set(unsigned long m, char t) {
        rep.miles = m;
        rep.type = t;
    }

    static void* operator new(size_t size);
    static void operator delete(void* deadObejct, size_t size);

private:
    struct AirplaneRep {
        usigned long miles;
        char type;
    };
    union {
        AirplaneRep rep;
        Airplane *next;
    }

private:
    static const int BLOCK_SIZE;
    static Airplane* headOfFreeList;
};

// 类内静态变量再次声明
const int Airplane::BLOCK_SIZE = 512;
Airplane* Airplane::headOfFreeList;

void* Airplane::operator new(size_t size) {
    // 如果有继承关系的时候，size会有区别
    if (size != sizeof(Airplace))
        return ::operator new(size);

    Airplane* p = headOfFreeTree;
    if (p) {
        // 还有空间
        headOfFreeTree = headOfFreeTree->next;
    } else {
        // 没有空间了，一次性分配多个空间
        Airplane* newBlock = static_cast<Airplane*>(::operator new(size * BLOCK_SIZE));
        // 链接分配的内存
        for(int i = 1; i < BLOCK_SIZE-1; ++i) {
            newBlock[i].next = &newBlock[i+1];
        }
        newBlock[BLOCK_SIZE-1].next = NULL;
        p = newBlock;
        headOfFreeTree = &newBlock[1];
    }

    return p;
}

void Airplane::operator delete(void* deadObject, size_t size)  {
    if (deadObject == 0) return;
    if (size != sizeof(Airplane)) {
        ::operator delete(deadObject);
        return;
    }

    Airplane* carcass = static_cast<Airplane*>(deadObject);

    carcass->next = headOfFreeTree;
    headOfFreeTree = carcass;
}
```



## 为什么要再次声明类内静态变量

- 类内定义非const的静态成员变量会导致静态成员被重复定义，所以在类外定义类内静态变量，分配内存
- 类内可以定义const的静态成员变量







## 14 封装 static allocator

#### 封装，不在需要每个类实现一遍

```c++
class allocator {
private:
    struct obj {
        struct obj* next;
    };
public:
    void* allocate(size_t);
    void deallocate(void*, size_t);
private:
    obj* freeStore = nullptr;
    const int CHUNK = 5;
}

void* allocator::allocate(size_t size) {
    obj* p;
    if (!freeStore) {
        size_t chunk = CHUNK * size;
        freeStore = p = (obj*)malloc(chunk);

        for (int i = 0; i < CHUNK-1; ++i) {
            p->next = (obj*)((char*)p+size);
            p = p->next;
        }
        p->next = nullptr;
    }
    p = freeStore;
    freeStore = freeStore->next;
    return p;
}

void allocator::deallocate(void* p, size_t) {
    ((obj*)p)->next = freeStore;
    freeStore = (obj*)p;
}

class F00 {
public:
    long L;
    string str;
    static allocator myAlloc;
public:
    Foo(long l):L(l) {}
    static void* operator new(size_t size) { return myAlloc::allocate(size); }
    static void operator delete(void pdead, size_t size) {return myAlloc::deallocate(pdead, size); }
}
allocator Foo::myAlloc;
```






## 15 macro for static allocator

#### 使用宏减轻代码量
![15-1](pic/memory/15-1.png)
